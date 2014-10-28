/****************************************************************************************
 * Copyright (c) 2014 Leo Franchi <lfranchi@kde.org>                                    *
 * Copyright (c) 2014 Stefan Derkits <stefan@derkits.at>                                *
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

#include "Genre.h"

#include "Genre_p.h"
#include "Parsing_p.h"

Echonest::Genre::Genre()
    : d( new GenreData )
{
    init();
}


Echonest::Genre::Genre( const Echonest::Genre& other )
    : d( other.d )
{
    init();
}


Echonest::Genre::Genre( const QString& name )
{
    init();
    setName( name );
}

Echonest::Genre& Echonest::Genre::operator=( const Echonest::Genre& genre )
{
    d = genre.d;
    return *this;
}


Echonest::Genre::~Genre()
{

}

void Echonest::Genre::init()
{
    qRegisterMetaType<Echonest::Genre>("Echonest::Genre");
}


QString Echonest::Genre::name() const
{
    return d->name;
}


void Echonest::Genre::setName( const QString& name )
{
    d->name = name;
}


Echonest::Artists Echonest::Genre::artists() const
{
    return d->artists;
}


void Echonest::Genre::setArtists( const Artists& artists )
{
    d->artists = artists;
}


QUrl Echonest::Genre::wikipediaUrl() const
{
    return d->wikipedia_url;
}


void Echonest::Genre::setWikipediaUrl( const QUrl& url )
{
    d->wikipedia_url = url;
}


QString Echonest::Genre::description() const
{
    return d->description;
}


void Echonest::Genre::setDescription( const QString& description )
{
    d->description = description;
}


QNetworkReply* Echonest::Genre::fetchArtists( ArtistInformation information, int numResults, bool limit )
{
    QUrl url = setupQuery( "artists", numResults );
    urlAddQueryItem( url, QLatin1String( "limit" ), QLatin1String( limit ? "true" : "false" ) );

    Artist::addQueryInformation( url, information );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Genre::fetchSimilar( GenreInformation information, int numResults, int start )
{
    QUrl url = setupQuery( "similar", numResults, start );
    addQueryInformation( url, information );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Genre::fetchProfile( const Echonest::Genres& genres, GenreInformation information )
{
    QUrl url = setupStaticQuery( "profile" );
    addQueryInformation( url, information );

    foreach( const Genre& g, genres )
        urlAddQueryItem( url, QLatin1String( "name" ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( g.name() ) ) );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Genre::fetchList( GenreInformation information, int numResults )
{
    QUrl url = setupStaticQuery( "list", numResults );
    addQueryInformation( url, information );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


QNetworkReply* Echonest::Genre::fetchSearch( const QString& name, Echonest::GenreInformation information, int numResults, int start )
{
    QUrl url = setupStaticQuery( "search", numResults );
    addQueryInformation( url, information );

    urlAddQueryItem( url, QLatin1String( "name" ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( name ) ) );

    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );
}


Echonest::Artists Echonest::Genre::parseArtists( QNetworkReply* reply ) throw( Echonest::ParseError )
{
   return Artist::parseSearch( reply );
}


Echonest::Genres Echonest::Genre::parseSimilar( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    return parseList( reply );
}


Echonest::Genres Echonest::Genre::parseProfile( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    return parseList( reply );
}


Echonest::Genres Echonest::Genre::parseList( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    Echonest::Parser::checkForErrors( reply );

    QXmlStreamReader xml( reply->readAll() );

    Echonest::Parser::readStatus( xml );

    Echonest::Genres genres = Echonest::Parser::parseGenres( xml );

    reply->deleteLater();
    return genres;
}


Echonest::Genres Echonest::Genre::parseSearch( QNetworkReply* reply ) throw( Echonest::ParseError )
{
   return parseList( reply );
}


QUrl Echonest::Genre::setupStaticQuery( const QByteArray& methodName, int numResults, int start )
{
    QUrl url = Echonest::baseGetQuery( "genre", methodName );

    if( numResults > 0 )
        urlAddQueryItem( url, QLatin1String( "results" ), QString::number( numResults ) );
    if( start >= 0 )
        urlAddQueryItem( url, QLatin1String( "start" ), QString::number( start ) );

    return url;
}


QUrl Echonest::Genre::setupQuery( const QByteArray& methodName, int numResults, int start) const
{
    QUrl url = setupStaticQuery( methodName, numResults, start );
    if( !d->name.isEmpty() ) {
        urlAddQueryItem( url, QLatin1String( "name" ), QString::fromLatin1( Echonest::escapeSpacesAndPluses( d->name ) ) );
    } else if ( methodName != "list" || methodName != "search" ) {
        qWarning() << "Genre method" << methodName << "called on a genre object without name or id!";
        return QUrl();
    }
    return url;
}


void Echonest::Genre::addQueryInformation( QUrl& url, Echonest::GenreInformation information )
{
    if( information.flags().testFlag( Echonest::GenreInformation::Description ) )
        urlAddQueryItem( url, QLatin1String( "bucket" ), QLatin1String( "description" ) );
    if( information.flags().testFlag( Echonest::GenreInformation::Urls ) )
        urlAddQueryItem( url, QLatin1String( "bucket" ), QLatin1String( "urls" ) );
}


QDebug Echonest::operator<<(QDebug d, const Echonest::Genre& genre)
{
    return d.maybeSpace() << QString::fromLatin1( "Genre(%1)" ).arg( genre.name() );
}
