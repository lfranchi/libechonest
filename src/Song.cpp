/****************************************************************************************
 * Copyright (c) 2010 Leo Franchi <lfranchi@kde.org>                                    *
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

#include "Song.h"

#include "Config.h"
#include "Types_p.h"

#include <QNetworkReply>
#include <QDebug>

#include <QtNetwork/QNetworkReply>

Echonest::Song::Song()
    : d( new SongData )
{}

Echonest::Song::Song( const QByteArray& xmlData )
  : d( new SongData )
{
  // parse xml
}

QString Echonest::Song::id() const
{
    return d->id;
}

void Echonest::Song::setId(const QString& id)
{
    d->id = id;
}


QString Echonest::Song::title() const
{
    return d->title;
}

void Echonest::Song::setTitle(const QString& title)
{
    d->title = title;
}

QString Echonest::Song::artistId() const
{
    return d->artistId;
}

void Echonest::Song::setArtistId(const QString& artistId)
{
    d->artistId = artistId;
}

QString Echonest::Song::artistName() const
{
    return d->artistName;
}

void Echonest::Song::setArtistName(const QString& artistName)
{
    d->artistName = artistName;
}

QNetworkReply* Echonest::Song::fetchInformation( Echonest::Song::SongInformation parts ) const
{
    QUrl url = Echonest::baseGetQuery( "song", "profile" );
    url.addEncodedQueryItem( "id", d->id.toUtf8() );
    if( parts.testFlag( Echonest::Song::AudioSummary ) )
        url.addEncodedQueryItem( "bucket", "audio_summary" );
    if( parts.testFlag( Echonest::Song::Tracks ) )
        url.addEncodedQueryItem( "bucket", "tracks" );
    if( parts.testFlag( Echonest::Song::Hotttnesss ) )
        url.addEncodedQueryItem( "bucket", "song_hotttnesss" );
    if( parts.testFlag( Echonest::Song::ArtistHotttnesss ) )
        url.addEncodedQueryItem( "bucket", "artist_hotttnesss" );
    if( parts.testFlag( Echonest::Song::ArtistFamiliarity ) )
        url.addEncodedQueryItem( "bucket", "artist_familiarity" );
    if( parts.testFlag( Echonest::Song::ArtistLocation ) )
        url.addEncodedQueryItem( "bucket", "artist_location" );
    
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Song::search( const Echonest::Song::SearchParams& params, Echonest::Song::SongInformation parts )
{
    QUrl url = Echonest::baseGetQuery( "song", "search" );
  
    SearchParams::const_iterator iter = params.constBegin();
    for( ; iter < params.constEnd(); ++iter )
        url.addQueryItem( QLatin1String( searchParamToString( iter->first ) ), iter->second.toString() );
    
    qDebug() << "Creating search URL" << url;
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QHash< Echonest::Song::SongInformationFlag, QVariant > Echonest::Song::parseInformation( QNetworkReply* reply )
{

}

QVector< Echonest::Song > Echonest::Song::parseSearch( QNetworkReply* reply )
{
    
    qDebug() << reply->readAll();
    
    QVector<Echonest::Song> songs;
    
    return songs;
    
}

QByteArray Echonest::Song::searchParamToString( Echonest::Song::SearchParam param )
{
    switch( param )
    {
        case Echonest::Song::Title:
            return "title";
        case Echonest::Song::Artist:
            return "artist";
        case Echonest::Song::Combined:
            return "combined";
        case Echonest::Song::Description:
            return "description";
        case Echonest::Song::ArtistId:
            return "artist_id";
        case Echonest::Song::Results:
            return "results";
        case Echonest::Song::MaxTempo:
            return "max_tempo";
        case Echonest::Song::MinTempo:
            return "min_tempo";
        case Echonest::Song::MaxDanceability:
            return "max_danceability";
        case Echonest::Song::MinDanceability:
            return "min_danceability";
        case Echonest::Song::MaxComplexity:
            return "max_complexity";
        case Echonest::Song::MinComplexity:
            return "min_complexity";
        case Echonest::Song::MaxDuration:
            return "max_duration";
        case Echonest::Song::MinDuration:
            return "min_duration";
        case Echonest::Song::MaxLoudness:
            return "max_loudness";
        case Echonest::Song::MinLoudness:
            return "min_loudness";
        case Echonest::Song::MaxFamiliarity:
            return "max_familiarity";
        case Echonest::Song::MinFamiliarity:
            return "min_familiarity";
        case Echonest::Song::MaxHotttnesss:
            return "max_hotttnesss";
        case Echonest::Song::MinHotttnesss:
            return "min_hotttnesss";
        case Echonest::Song::MaxLongitude:
            return "max_longitude";
        case Echonest::Song::MinLongitude:
            return "min_longitude";
        case Echonest::Song::Mode:
            return "mode";
        case Echonest::Song::Key:
            return "key";
        case Echonest::Song::Sort:
            return "sort";
    }
    return QByteArray();
}


