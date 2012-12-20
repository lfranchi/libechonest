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

#include "Artist.h"
#include "Artist_p.h"
#include "ArtistTypes.h"
#include "Parsing_p.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

Echonest::Artist::Artist()
    : d( new ArtistData )
{
    init();
}

Echonest::Artist::Artist( const QByteArray& id, const QString& name )
    : d( new ArtistData )
{
    init();
    d->id = id;
    d->name = name;
}

Echonest::Artist::Artist( const QString& name )
    : d( new ArtistData )
{
    init();
    setName( name );
}

Echonest::Artist::Artist( const QByteArray& id )
: d( new ArtistData )
{
    init();
    setId( id );
}
Echonest::Artist::Artist(const Echonest::Artist& other)
    : d( other.d )
{
    init();
}

Echonest::Artist& Echonest::Artist::operator=(const Echonest::Artist& artist)
{
    d = artist.d;
    return *this;
}

Echonest::Artist::~Artist()
{

}

void Echonest::Artist::init()
{
    qRegisterMetaType<Echonest::Artist>("Echonest::Artist");
}

QByteArray Echonest::Artist::id() const
{
    return d->id;
}

QString Echonest::Artist::name() const
{
    return d->name;
}

void Echonest::Artist::setId(const QByteArray& id)
{
    d->id = id;
}

void Echonest::Artist::setName(const QString& name)
{
    d->name = name;
}

Echonest::AudioList Echonest::Artist::audio() const
{
    return d->audio;
}

void Echonest::Artist::setAudio(const Echonest::AudioList& audio)
{
    d->audio = audio;
}


Echonest::BiographyList Echonest::Artist::biographies() const
{
    return d->biographies;
}

void Echonest::Artist::setBiographies(const Echonest::BiographyList& bios )
{
    d->biographies = bios;
}

Echonest::BlogList Echonest::Artist::blogs() const
{
    return d->blogs;
}

void Echonest::Artist::setBlogs(const Echonest::BlogList& blogs )
{
    d->blogs = blogs;
}

qreal Echonest::Artist::familiarity() const
{
    return d->familiarity;
}

void Echonest::Artist::setFamiliarity(qreal familiar)
{
    d->familiarity = familiar;
}

qreal Echonest::Artist::hotttnesss() const
{
    return d->hotttnesss;
}

void Echonest::Artist::setHotttnesss(qreal hotttnesss)
{
    d->hotttnesss = hotttnesss;
}

Echonest::ArtistImageList Echonest::Artist::images() const
{
    return d->images;
}

void Echonest::Artist::setImages(const Echonest::ArtistImageList& imgs)
{
    d->images = imgs;
}

Echonest::NewsList Echonest::Artist::news() const
{
    return d->news;
}

void Echonest::Artist::setNews(const Echonest::NewsList& news)
{
    d->news = news;
}

Echonest::ReviewList Echonest::Artist::reviews() const
{
    return d->reviews;
}

void Echonest::Artist::setReviews(const Echonest::ReviewList& reviews)
{
    d->reviews = reviews;
}

Echonest::SongList Echonest::Artist::songs() const
{
    return d->songs;
}

void Echonest::Artist::setSongs(const Echonest::SongList& songs)
{
    d->songs = songs;
}

Echonest::TermList Echonest::Artist::terms() const
{
    return d->terms;
}

void Echonest::Artist::setTerms(const Echonest::TermList& terms)
{
    d->terms = terms;
}

QUrl Echonest::Artist::amazonUrl() const
{
    return d->amazon_url;
}

void Echonest::Artist::setVideos(const Echonest::VideoList& videos)
{
    d->videos = videos;
}

void Echonest::Artist::setAmazonUrl(const QUrl& url)
{
    d->amazon_url = url;
}


QUrl Echonest::Artist::aolMusicUrl() const
{
    return d->aolmusic_url;
}

void Echonest::Artist::setAolMusicUrl(const QUrl& url)
{
    d->aolmusic_url = url;
}

QUrl Echonest::Artist::itunesUrl() const
{
    return d->itunes_url;
}

void Echonest::Artist::setItunesUrl( const QUrl& url )
{
    d->itunes_url = url;
}

QUrl Echonest::Artist::lastFmUrl() const
{
    return d->lastfm_url;
}

void Echonest::Artist::setLastFmUrl(const QUrl& url )
{
    d->lastfm_url = url;
}

QUrl Echonest::Artist::myspaceUrl() const
{
    return d->myspace_url;
}

void Echonest::Artist::setMyspaceUrl( const QUrl& url )
{
    d->myspace_url = url;
}

QUrl Echonest::Artist::musicbrainzUrl() const
{
    return d->mb_url;
}

void Echonest::Artist::setMusicbrainzUrl(const QUrl& url)
{
    d->mb_url = url;
}


Echonest::VideoList Echonest::Artist::videos() const
{
    return d->videos;
}

Echonest::ForeignIds Echonest::Artist::foreignIds() const
{
    return d->foreign_ids;
}

void Echonest::Artist::setForeignIds(const Echonest::ForeignIds& ids)
{
    d->foreign_ids = ids;
}

QNetworkReply* Echonest::Artist::fetchAudio(int numResults, int offset) const
{
    QUrl url = setupQuery( "audio", numResults, offset );
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchBiographies(const QString& license, int numResults, int offset) const
{
    QUrl url = setupQuery( "biographies", numResults, offset );

    QUrlQuery urlQuery( url );
    if( !license.isEmpty() )
        urlQuery.addQueryItem( QLatin1String( "license" ), license );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchBlogs( bool highRelevanceOnly, int numResults, int offset ) const
{
    QUrl url = setupQuery( "blogs", numResults, offset );

    QUrlQuery urlQuery( url );
    if( highRelevanceOnly ) // false is default
        urlQuery.addQueryItem( QLatin1String( "high_relevance" ), QLatin1String( "true" ) );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchFamiliarity() const
{
    QUrl url = setupQuery( "familiarity", 0, -1 );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchHotttnesss(const QString& type) const
{
    QUrl url = setupQuery( "hotttnesss", 0, -1 );

    QUrlQuery urlQuery( url );
    if( type != QLatin1String( "normal" ) )
        urlQuery.addQueryItem( QLatin1String( "type" ), type );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchImages( const QString& license, int numResults, int offset ) const
{
    QUrl url = setupQuery( "images", numResults, offset );

    QUrlQuery urlQuery( url );
    if( !license.isEmpty() )
        urlQuery.addQueryItem( QLatin1String( "license" ), license );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchProfile(Echonest::ArtistInformation information) const
{
    QUrl url = setupQuery( "profile", 0, -1 );
    addQueryInformation( url, information );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchNews( bool highRelevanceOnly, int numResults, int offset ) const
{
    QUrl url = setupQuery( "news", numResults, offset );

    QUrlQuery urlQuery( url );
    if( highRelevanceOnly ) // false is default
        urlQuery.addQueryItem( QLatin1String( "high_relevance" ), QLatin1String( "true" ) );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchReviews(int numResults, int offset) const
{
    QUrl url = setupQuery( "reviews", numResults, offset );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchSimilar(const Echonest::Artist::SearchParams& params, Echonest::ArtistInformation information, int numResults, int offset )
{
    QUrl url = Echonest::baseGetQuery( "artist", "similar" );
    addQueryInformation( url, information );

    QUrlQuery urlQuery( url );
    if( numResults > 0 )
        urlQuery.addQueryItem( QLatin1String( "results" ), QString::number( numResults ) );
    if( offset >= 0 )
        urlQuery.addQueryItem( QLatin1String( "start" ), QString::number( offset ) );

    Echonest::Artist::SearchParams::const_iterator iter = params.constBegin();
    for( ; iter < params.constEnd(); ++iter )
        urlQuery.addQueryItem( QString::fromLatin1( searchParamToString( iter->first ) ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( iter->second.toString() ) ) );

    url.setQuery( urlQuery );
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchSongs( int numResults, int offset  ) const
{
    QUrl url = setupQuery( "songs", numResults, offset );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchTerms( Echonest::Artist::TermSorting sorting ) const
{
    QUrl url = setupQuery( "terms", 0, -1 );

    QUrlQuery urlQuery( url );
    if( sorting == Echonest::Artist::Weight )
        urlQuery.addQueryItem( QLatin1String( "sort" ), QLatin1String( "weight" ) );
    else if( sorting == Echonest::Artist::Frequency )
        urlQuery.addQueryItem( QLatin1String( "sort" ), QLatin1String( "frequency" ) );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Artist::fetchUrls() const
{
    QUrl url = setupQuery( "urls", 0, -1 );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::fetchVideo(int numResults, int offset) const
{
    QUrl url = setupQuery( "video", numResults, offset );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply *Echonest::Artist::fetchGenres()
{
    QUrl url = baseGetQuery( "artist", "list_genres" );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Artist::search(const Echonest::Artist::SearchParams& params, Echonest::ArtistInformation information, bool limit)
{
    QUrl url = Echonest::baseGetQuery( "artist", "search" );

    Echonest::Artist::SearchParams::const_iterator iter = params.constBegin();

    QUrlQuery urlQuery( url );
    for( ; iter < params.constEnd(); ++iter )
        urlQuery.addQueryItem( QString::fromLatin1( searchParamToString( iter->first ) ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( iter->second.toString() ) ) );
    urlQuery.addQueryItem( QLatin1String( "limit" ), QLatin1String( limit ? "true" : "false" ) );
    url.setQuery( urlQuery );

    addQueryInformation( url, information );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::topHottt(Echonest::ArtistInformation information, int numResults, int offset, bool limit)
{
    QUrl url = Echonest::baseGetQuery( "artist", "top_hottt" );
    addQueryInformation( url, information );

    QUrlQuery urlQuery( url );
    if( numResults > 0 )
        urlQuery.addQueryItem( QLatin1String( "results" ), QString::number( numResults ) );
    if( offset >= 0 )
        urlQuery.addQueryItem( QLatin1String( "start" ), QString::number( offset ) );

    urlQuery.addQueryItem( QLatin1String( "limit" ), QLatin1String( limit ? "true" : "false" ) );

    url.setQuery( urlQuery );
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::topTerms(int numResults)
{
    QUrl url = Echonest::baseGetQuery( "artist", "top_terms" );

    QUrlQuery urlQuery( url );
    urlQuery.addQueryItem( QLatin1String( "results" ), QString::number( numResults ) );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}

QNetworkReply* Echonest::Artist::listTerms( const QString& type )
{
    QUrl url = Echonest::baseGetQuery( "artist", "list_terms" );

    QUrlQuery urlQuery( url );
    urlQuery.addQueryItem( QLatin1String( "type" ), type );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Artist::suggest( const QString& name, int results )
{
    QUrl url = Echonest::baseGetQuery( "artist", "suggest" );
    QString realname = name;

    QUrlQuery urlQuery( url );
    urlQuery.addQueryItem( QLatin1String( "name" ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( realname ) ) );
    urlQuery.addQueryItem( QLatin1String( "results" ), QString::number( results ) );
    url.setQuery( urlQuery );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


int Echonest::Artist::parseProfile( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    int numResults = Echonest::Parser::parseArtistInfoOrProfile( xml, *this );

    reply->deleteLater();
    return numResults;
}

Echonest::Artists Echonest::Artist::parseSearch( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QByteArray data = reply->readAll();
    QXmlStreamReader xml( data );

    Echonest::Parser::readStatus( xml );

    Echonest::Artists artists = Echonest::Parser::parseArtists( xml );

    reply->deleteLater();
    return artists;
}

Echonest::Artists Echonest::Artist::parseSimilar( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    return parseSearch( reply );
}

Echonest::Artists Echonest::Artist::parseTopHottt( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    return parseSearch( reply );
}

Echonest::TermList Echonest::Artist::parseTopTerms( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    Echonest::TermList terms = Echonest::Parser::parseTopTermList( xml );

    reply->deleteLater();
    return terms;
}

Echonest::Artists Echonest::Artist::parseSuggest( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    Echonest::Artists artists = Echonest::Parser::parseArtistSuggestList( xml );

    reply->deleteLater();
    return artists;
}

QVector< QString > Echonest::Artist::parseTermList( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    QVector< QString > terms = Echonest::Parser::parseTermList( xml );

    reply->deleteLater();
    return terms;
}

QVector< QString > Echonest::Artist::parseGenreList( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    QVector< QString > genres = Echonest::Parser::parseGenreList( xml );

    reply->deleteLater();
    return genres;
}

QUrl Echonest::Artist::setupQuery( const QByteArray& methodName, int numResults, int start ) const
{
    QUrl url = Echonest::baseGetQuery( "artist", methodName );

    QUrlQuery urlQuery( url );

    if( !d->id.isEmpty() )
        urlQuery.addQueryItem( QLatin1String( "id" ), QString::fromLatin1( d->id ) );
    else if( !d->name.isEmpty() ) {
        urlQuery.addQueryItem( QLatin1String( "name" ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( d->name ) ) );
    } else if ( methodName != "terms" ) {
        qWarning() << "Artist method" << methodName << "called on an artist object without name or id!";
        return QUrl();
    }
    if( numResults > 0 )
        urlQuery.addQueryItem( QLatin1String( "results" ), QString::number( numResults ) );
    if( start >= 0 )
        urlQuery.addQueryItem( QLatin1String( "start" ), QString::number( start ) );

    url.setQuery( urlQuery );

    return url;
}

QByteArray Echonest::Artist::searchParamToString(Echonest::Artist::SearchParam param)
{
    switch( param )
    {
        case Id:
            return "id";
        case Name:
            return "name";
        case Results:
            return "results";
        case Description:
            return "description";
        case FuzzyMatch:
            return "fuzzy_match";
        case MaxFamiliarity:
            return "max_familiarity";
        case MinFamiliarity:
            return "min_familiarity";
        case MaxHotttnesss:
            return "max_hotttnesss";
        case MinHotttnesss:
            return "min_hotttnesss";
        case Reverse:
            return "reverse";
        case Sort:
            return "sort";
        case Mood:
            return "mood";
        default:
            return "";
    }
}

void Echonest::Artist::addQueryInformation(QUrl& url, Echonest::ArtistInformation information)
{
    QUrlQuery urlQuery( url );

    if( information.flags().testFlag( Echonest::ArtistInformation::Audio ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "audio" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Biographies ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "biographies" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Blogs ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "blogs" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Familiarity ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "familiarity" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Hotttnesss ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "hotttnesss" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Images ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "images" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::News ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "news" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Reviews ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "reviews" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Terms ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "terms" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Urls ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "urls" ) );
    if( information.flags().testFlag( Echonest::ArtistInformation::Videos ) )
        urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "video" ) );

    if( !information.idSpaces().isEmpty() ) {
        foreach( const QString& idSpace, information.idSpaces() )
            urlQuery.addQueryItem( QLatin1String( "bucket" ), QLatin1String( "id:" + idSpace.toUtf8() ) );
    }

    url.setQuery( urlQuery );
}


QDebug Echonest::operator<<(QDebug d, const Echonest::Artist& artist)
{
    return d.maybeSpace() << QString::fromLatin1( "Artist(%1, %2)" ).arg( artist.name() ).arg( QString::fromLatin1(artist.id()) );
}

