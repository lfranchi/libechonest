/****************************************************************************************
 * Copyright (c) 2010-2012 Leo Franchi <lfranchi@kde.org>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 2 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#include "Playlist.h"
#include "Playlist_p.h"
#include "Parsing_p.h"
#include <QtNetwork/QNetworkReply>

Echonest::DynamicPlaylist::DynamicPlaylist()
    : d( new DynamicPlaylistData )
{

}

Echonest::DynamicPlaylist::DynamicPlaylist(const Echonest::DynamicPlaylist& other)
    : d( other.d )
{

}

Echonest::DynamicPlaylist::~DynamicPlaylist()
{

}


Echonest::DynamicPlaylist& Echonest::DynamicPlaylist::operator=(const Echonest::DynamicPlaylist& playlist)
{
    d = playlist.d;
    return *this;
}

QNetworkReply* Echonest::DynamicPlaylist::create(const Echonest::DynamicPlaylist::PlaylistParams& params) const
{
    // params are the same, if user passes in format parsing will throw, but it should be expected..
    return generateInternal( params, "dynamic/create" );
}

void Echonest::DynamicPlaylist::parseCreate(QNetworkReply* reply) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );
    QByteArray data = reply->readAll();
//     qDebug() << data;
    QXmlStreamReader xml( data );

    Echonest::Parser::readStatus( xml );
    d->sessionId = Echonest::Parser::parsePlaylistSessionId( xml );


    Q_ASSERT( !d->sessionId.isEmpty() );
}

QNetworkReply* Echonest::DynamicPlaylist::restart(const Echonest::DynamicPlaylist::PlaylistParams& params) const
{
    return generateInternal( params, "dynamic/restart" );
}

QByteArray Echonest::DynamicPlaylist::sessionId() const
{
    return d->sessionId;
}

void Echonest::DynamicPlaylist::setSessionId(const QByteArray& id)
{
    d->sessionId = id;
}

Echonest::Song Echonest::DynamicPlaylist::currentSong() const
{
    return d->currentSong;
}

void Echonest::DynamicPlaylist::setCurrentSong(const Echonest::Song& song)
{
    d->currentSong = song;
}

QNetworkReply* Echonest::DynamicPlaylist::next( int results, int lookahead ) const
{
    QUrl url = Echonest::baseGetQuery( "playlist/dynamic", "next" );
    url.addEncodedQueryItem( "session_id", d->sessionId );
    url.addEncodedQueryItem( "results", QByteArray::number( results ) );
    url.addEncodedQueryItem( "lookahead", QByteArray::number( lookahead ) );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::DynamicPlaylist::fetchInfo() const
{
    QUrl url = Echonest::baseGetQuery( "playlist/dynamic", "info" );
    url.addEncodedQueryItem( "session_id", d->sessionId );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QPair<Echonest::SongList, Echonest::SongList> Echonest::DynamicPlaylist::parseNext(QNetworkReply* reply) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

//     const QByteArray data = reply->readAll();
//     qDebug() << data;
    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );
    
    Echonest::SongList lookahead = Echonest::Parser::parseDynamicLookahead( xml );
    Echonest::SongList results = Echonest::Parser::parseSongList( xml );
    
    reply->deleteLater();

    return qMakePair(results, lookahead);
}

QNetworkReply* Echonest::DynamicPlaylist::feedback(const Echonest::DynamicPlaylist::DynamicFeedback& feedback) const
{
    QUrl url = Echonest::baseGetQuery( "playlist/dynamic", "feedback" );
    url.addEncodedQueryItem( "session_id", d->sessionId );

    foreach( const Echonest::DynamicPlaylist::DynamicFeedbackParamData& param, feedback ) {
        url.addEncodedQueryItem(dynamicFeedbackToString(param.first), param.second);
    }
    
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

void Echonest::DynamicPlaylist::parseFeedback(QNetworkReply* reply) const throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    reply->deleteLater();
}

QNetworkReply* Echonest::DynamicPlaylist::steer(const Echonest::DynamicPlaylist::PlaylistParams& steerParams) const
{
    QUrl url = Echonest::baseGetQuery( "playlist/dynamic", "steer" );
    url.addEncodedQueryItem( "session_id", d->sessionId );

    foreach( const Echonest::DynamicPlaylist::PlaylistParamData& param, steerParams ) {
        // HACK ARG min/max functions for steering are min_foo_bar, but params for static/initial seeds are foo_min_bar. can't reuse :(
        QByteArray str;
        switch ( param.first )
        {
            case Echonest::DynamicPlaylist::ArtistMinFamiliarity:
                str = "min_artist_familiarity";
                break;
            case Echonest::DynamicPlaylist::ArtistMaxFamiliarity:
                str = "max_artist_familiarity";
                break;
            case Echonest::DynamicPlaylist::ArtistMinHotttnesss:
                str = "min_artist_hotttnesss";
                break;
            case Echonest::DynamicPlaylist::ArtistMaxHotttnesss:
                str = "max_artist_hotttnesss";
                break;
            case Echonest::DynamicPlaylist::SongMinHotttnesss:
                str = "min_song_hotttnesss";
                break;
            case Echonest::DynamicPlaylist::SongMaxHotttnesss:
                str = "max_song_hotttnesss";
                break;
            case Echonest::DynamicPlaylist::MinEnergy:
                str = "min_energy";
                break;
            case Echonest::DynamicPlaylist::MaxEnergy:
                str = "max_energy";
                break;
            case Echonest::DynamicPlaylist::MinDanceability:
                str = "min_danceability";
                break;
            case Echonest::DynamicPlaylist::MaxDanceability:
                str = "max_danceability";
                break;
            case Echonest::DynamicPlaylist::MinLoudness:
                str = "min_loudness";
                break;
            case Echonest::DynamicPlaylist::MaxLoudness:
                str = "max_loudness";
                break;
            case Echonest::DynamicPlaylist::MinTempo:
                str = "min_tempo";
                break;
            case Echonest::DynamicPlaylist::MaxTempo:
                str = "max_tempo";
                break;
            default:
                str = playlistParamToString( param.first );
        }
        url.addEncodedQueryItem(str, param.second.toString().toUtf8());
    }

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

void Echonest::DynamicPlaylist::parseSteer(QNetworkReply* reply) const throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );
    
    reply->deleteLater();
}

Echonest::SessionInfo Echonest::DynamicPlaylist::parseInfo(QNetworkReply* reply) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    reply->deleteLater();
    return Echonest::Parser::parseSessionInfo( xml );

}

QNetworkReply* Echonest::DynamicPlaylist::deleteSession() const
{
    QUrl url = Echonest::baseGetQuery( "playlist/dynamic", "delete" );
    url.addEncodedQueryItem( "session_id", d->sessionId );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

void Echonest::DynamicPlaylist::parseDeleteSession(QNetworkReply* reply)
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    d->sessionId.clear();

    reply->deleteLater();
}

QNetworkReply* Echonest::DynamicPlaylist::staticPlaylist(const Echonest::DynamicPlaylist::PlaylistParams& params)
{
    return Echonest::DynamicPlaylist::generateInternal( params, "static" );
}

Echonest::SongList Echonest::DynamicPlaylist::parseStaticPlaylist(QNetworkReply* reply) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    Echonest::SongList songs = Echonest::Parser::parseSongList( xml );
    reply->deleteLater();
    return songs;
}

QByteArray Echonest::DynamicPlaylist::parseXSPFPlaylist(QNetworkReply* reply) throw( Echonest::ParseError )
{
    QByteArray data = reply->readAll();
    Echonest::Parser::checkForErrors( reply );

    reply->deleteLater();
    return data;
}

QNetworkReply* Echonest::DynamicPlaylist::generateInternal(const Echonest::DynamicPlaylist::PlaylistParams& params, const QByteArray& type)
{
    QUrl url = Echonest::baseGetQuery( "playlist", type );

    Echonest::DynamicPlaylist::PlaylistParams::const_iterator iter = params.constBegin();
    for( ; iter < params.constEnd(); ++iter ) {
        if( iter->first == Format ) // If it's a format, we have to remove the xml format we automatically specify
            url.removeEncodedQueryItem( "format" );

        if( iter->first == Type ) { // convert type enum to string
            switch( static_cast<Echonest::DynamicPlaylist::ArtistTypeEnum>( iter->second.toInt() ) )
            {
            case ArtistType:
                url.addEncodedQueryItem(  playlistParamToString( iter->first ), "artist" );
                break;
            case ArtistRadioType:
                url.addEncodedQueryItem(  playlistParamToString( iter->first ), "artist-radio" );
                break;
            case ArtistDescriptionType:
                url.addEncodedQueryItem(  playlistParamToString( iter->first ), "artist-description" );
                break;
            case CatalogType:
                url.addEncodedQueryItem(  playlistParamToString( iter->first ), "catalog" );
                break;
            case CatalogRadioType:
                url.addEncodedQueryItem(  playlistParamToString( iter->first ), "catalog-radio" );
                break;
            case SongRadioType:
                url.addEncodedQueryItem(  playlistParamToString( iter->first ), "song-radio" );
                break;
            }

        } else if( iter->first == Sort ) {
            url.addEncodedQueryItem( playlistParamToString( iter->first ), playlistSortToString( static_cast<Echonest::DynamicPlaylist::SortingType>( iter->second.toInt() ) ) );
        } else if( iter->first == Pick ) {
            url.addEncodedQueryItem( playlistParamToString( iter->first ), playlistArtistPickToString( static_cast<Echonest::DynamicPlaylist::ArtistPick>( iter->second.toInt() ) ) );
        } else if( iter->first == SongInformation ){
            Echonest::Song::addQueryInformation( url, Echonest::SongInformation( iter->second.value< Echonest::SongInformation >() ) );
        } else {
            url.addEncodedQueryItem( playlistParamToString( iter->first ), Echonest::escapeSpacesAndPluses( iter->second.toString() ) );
        }
    }

//     qDebug() << "Creating playlist URL" << url;
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QByteArray Echonest::DynamicPlaylist::playlistParamToString(Echonest::DynamicPlaylist::PlaylistParam param)
{
    switch( param )
    {
        case Echonest::DynamicPlaylist::Type :
            return "type";
        case Echonest::DynamicPlaylist::Format :
            return "format";
        case Echonest::DynamicPlaylist::Pick:
            return "artist_pick";
        case Echonest::DynamicPlaylist::Variety :
            return "variety";
        case Echonest::DynamicPlaylist::ArtistId :
            return "artist_id";
        case Echonest::DynamicPlaylist::Artist :
            return "artist";
        case Echonest::DynamicPlaylist::ArtistSeedCatalog :
            return "artist_seed_catalog";
        case Echonest::DynamicPlaylist::SourceCatalog :
            return "seed_catalog";
        case Echonest::DynamicPlaylist::SongId :
            return "song_id";
        case Echonest::DynamicPlaylist::Description :
            return "description";
        case Echonest::DynamicPlaylist::Results :
            return "results";
        case Echonest::DynamicPlaylist::MaxTempo :
            return "max_tempo";
        case Echonest::DynamicPlaylist::MinTempo :
            return "min_tempo";
        case Echonest::DynamicPlaylist::MaxDuration :
            return "max_duration";
        case Echonest::DynamicPlaylist::MinDuration :
            return "min_duration";
        case Echonest::DynamicPlaylist::MaxLoudness :
            return "max_loudness";
        case Echonest::DynamicPlaylist::MinLoudness :
            return "min_loudness";
        case Echonest::DynamicPlaylist::ArtistMaxFamiliarity :
            return "artist_max_familiarity";
        case Echonest::DynamicPlaylist::ArtistMinFamiliarity :
            return "artist_min_familiarity";
        case Echonest::DynamicPlaylist::MinDanceability :
            return "min_danceability";
        case Echonest::DynamicPlaylist::MaxDanceability :
            return "max_danceability";
        case Echonest::DynamicPlaylist::MinEnergy :
            return "min_energy";
        case Echonest::DynamicPlaylist::MaxEnergy :
            return "max_energy";
        case Echonest::DynamicPlaylist::ArtistMaxHotttnesss :
            return "artist_max_hotttnesss";
        case Echonest::DynamicPlaylist::ArtistMinHotttnesss :
            return "artist_min_hotttnesss";
        case Echonest::DynamicPlaylist::SongMaxHotttnesss :
            return "song_max_hotttnesss";
        case Echonest::DynamicPlaylist::SongMinHotttnesss :
            return "song_min_hotttnesss";
        case Echonest::DynamicPlaylist::ArtistMinLongitude :
            return "min_longitude";
        case Echonest::DynamicPlaylist::ArtistMaxLongitude :
            return "max_longitude";
        case Echonest::DynamicPlaylist::ArtistMinLatitude  :
            return "min_latitude";
        case Echonest::DynamicPlaylist::ArtistMaxLatitude :
            return "max_latitude";
        case Echonest::DynamicPlaylist::Mode :
            return "mode";
        case Echonest::DynamicPlaylist::Key :
            return "key";
        case Echonest::DynamicPlaylist::SongInformation:
            return "bucket";
        case Echonest::DynamicPlaylist::Sort :
            return "sort";
        case Echonest::DynamicPlaylist::Limit :
            return "limit";
        case Echonest::DynamicPlaylist::Audio :
            return "audio";
        case Echonest::DynamicPlaylist::DMCA :
            return "dmca";
        case Echonest::DynamicPlaylist::ChainXSPF :
            return "chain_xspf";
        case Echonest::DynamicPlaylist::Mood :
            return "mood";
        case Echonest::DynamicPlaylist::Style :
            return "style";
        case Echonest::DynamicPlaylist::Adventurousness :
            return "adventurousness";
        case Echonest::DynamicPlaylist::MoreLikeThis :
            return "more_like_this";
        case Echonest::DynamicPlaylist::LessLikeThis :
            return "less_like_this";
        case Echonest::DynamicPlaylist::TargetTempo :
            return "target_tempo";
        case Echonest::DynamicPlaylist::TargetDanceability :
            return "target_danceability";
        case Echonest::DynamicPlaylist::TargetEnergy :
            return "target_energy";
        case Echonest::DynamicPlaylist::TargetLoudness :
            return "target_loudness";
        case Echonest::DynamicPlaylist::TargetArtistFamiliarity :
            return "target_artist_familiarity";
        case Echonest::DynamicPlaylist::TargetArtistHotttnesss :
            return "target_artist_hotttnesss";
        case Echonest::DynamicPlaylist::TargetSongHotttnesss :
            return "target_song_hotttnesss";
    }
    return QByteArray();
}

QByteArray Echonest::DynamicPlaylist::playlistArtistPickToString(Echonest::DynamicPlaylist::ArtistPick pick)
{
    switch( pick )
    {
        case PickSongHotttnesssAscending:
            return "song_hotttnesss-asc";
        case PickTempoAscending:
            return "tempo-asc";
        case PickDurationAscending:
            return "duration-asc";
        case PickLoudnessAscending:
            return "loudness-asc";
        case PickModeAscending:
            return "mode-asc";
        case PickKeyAscending:
            return "key-asc";
        case PickSongHotttnesssDescending:
            return "song_hotttnesss-desc";
        case PickTempoDescending:
            return "tempo-desc";
        case PickDurationDescending:
            return "duration-desc";
        case PickLoudnessDescending:
            return "loudness-desc";
        case PickModeDescending:
            return "mode-desc";
        case PickKeyDescending:
            return "key-desc";
    }
    return QByteArray();
}

QByteArray Echonest::DynamicPlaylist::playlistSortToString(Echonest::DynamicPlaylist::SortingType sorting)
{
    switch( sorting )
    {
        case SortTempoAscending:
            return "tempo-asc";
        case SortTempoDescending:
            return "tempo-desc";
        case SortDurationAscending:
            return "duration-asc";
        case SortDurationDescending:
            return "duration-desc";
        case SortLoudnessAscending:
            return "loudness-asc";
        case SortLoudnessDescending:
            return "loudness-desc";
        case SortArtistFamiliarityAscending:
            return "artist_familiarity-asc";
        case SortArtistFamiliarityDescending:
            return "artist_familiarity-desc";
        case SortArtistHotttnessAscending:
            return "artist_hotttnesss-asc";
        case SortArtistHotttnessDescending:
            return "artist_hotttnesss-desc";
        case SortSongHotttnesssAscending:
            return "song_hotttnesss-asc";
        case SortSongHotttnesssDescending:
            return "song_hotttnesss-desc";
        case SortLatitudeAscending:
            return "latitude-asc";
        case SortLatitudeDescending:
            return "latitude-desc";
        case SortLongitudeAscending:
            return "longitude-asc";
        case SortLongitudeDescending:
            return "longitude-desc";
        case SortModeAscending:
            return "mode-asc";
        case SortModeDescending:
            return "mode-desc";
        case SortKeyAscending:
            return "key-asc";
        case SortKeyDescending:
            return "key-desc";
        case SortEnergyAscending:
            return "energy-asc";
        case SortEnergyDescending:
            return "energy-desc";
        case SortDanceabilityAscending:
            return "danceability-asc";
        case SortDanceabilityDescending:
            return "danceability-desc";
    }
    return QByteArray();
}

QByteArray Echonest::DynamicPlaylist::dynamicControlToString(Echonest::DynamicPlaylist::DynamicControlItem control)
{
    switch( control )
    {
        case Steer:
            return "steer";
        case SteerDescription:
            return "steer_description";
        case Rating:
            return "rating";
        case Ban:
            return "ban";
        default:
            return "";
    }
}

QByteArray Echonest::DynamicPlaylist::dynamicFeedbackToString(Echonest::DynamicPlaylist::DynamicFeedbackParam param)
{
    switch( param )
    {
        case BanArtist:
            return "ban_artist";
        case FavoriteArtist:
            return "favorite_artist";
        case BanSong:
            return "ban_song";
        case FavoriteSong:
            return "favorite_song";
        case SkipSong:
            return "skip_song";
        case PlaySong:
            return "play_song";
        case UnplaySong:
            return "unplay_song";
        case RateSong:
            return "rate_song";
        default:
            Q_ASSERT(false);
            return "";
    }
}

QDebug Echonest::operator<<(QDebug d, const Echonest::DynamicPlaylist& playlist)
{
    d << QString::fromLatin1( "DynamicPlaylist(%1, %2)" ).arg( QLatin1String( playlist.sessionId() ), playlist.currentSong().toString() );
    return d.maybeSpace();
}
