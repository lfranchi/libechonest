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

#include "Catalog.h"

#include "Catalog_p.h"

Echonest::Catalog::Catalog()
    : d( new CatalogData )
{

}

Echonest::Catalog::Catalog(const QString& name)
    : d( new CatalogData )
{
    d->name = name;
}


Echonest::Catalog::Catalog( const QByteArray& id )
    : d( new CatalogData )
{
    d->id = id;
}


Echonest::Catalog::Catalog( const Echonest::Catalog& catalog )
    : d( catalog.d )
{
}

Echonest::Catalog& Echonest::Catalog::operator=( const Echonest::Catalog& other )
{
    d = other.d;
    return *this;
}

Echonest::Catalog::~Catalog()
{
}

Echonest::CatalogArtists Echonest::Catalog::artists() const
{
    return d->artists;
}

void Echonest::Catalog::setArtists(const Echonest::CatalogArtists& artists)
{
    d->artists = artists;
}

QByteArray Echonest::Catalog::id() const
{
    return d->id;
}

void Echonest::Catalog::setId(const QByteArray& id)
{
    d->id = id;
}

QString Echonest::Catalog::name() const
{
    return d->name;
}

void Echonest::Catalog::setName(const QString& name)
{
    d->name = name;
}

int Echonest::Catalog::resolved() const
{
    return d->resolved;
}

void Echonest::Catalog::setResolved(int resolved)
{
    d->resolved = resolved;
}

int Echonest::Catalog::pendingTickets() const
{
//     return d->pending_tickets;
    return 0;
}

void Echonest::Catalog::setPendingTickets(int pending)
{
//     d->pending_tickets = pending;
}

Echonest::CatalogSongs Echonest::Catalog::songs() const
{
    return d->songs;
}

void Echonest::Catalog::setSongs(const Echonest::CatalogSongs& songs)
{
    d->songs = songs;
}

int Echonest::Catalog::total() const
{
    return d->total;
}

void Echonest::Catalog::setTotal(int total)
{
    d->total = total;
}

Echonest::CatalogTypes::Type Echonest::Catalog::type() const
{
    return d->type;
}

void Echonest::Catalog::setType(Echonest::CatalogTypes::Type type)
{
    d->type = type;
}

QNetworkReply* Echonest::Catalog::create(const QString& name, Echonest::CatalogTypes::Type type)
{
    QUrl url = Echonest::baseGetQuery( "catalog", "create" );
    url.addQueryItem( QLatin1String( "name" ), name );
    url.addEncodedQueryItem( "type", Echonest::catalogTypeToLiteral( type ) );
    
    QNetworkRequest request( url );
    request.setHeader( QNetworkRequest::ContentTypeHeader, QLatin1String( "multipart/form-data" ) );
    qDebug() << "Creating catalog::create URL" << url;
    return Echonest::Config::instance()->nam()->post( request, QByteArray() );
}

QNetworkReply* Echonest::Catalog::deleteCatalog()
{
    QUrl url = Echonest::baseGetQuery( "catalog", "delete" );
    url.addEncodedQueryItem( "id", d->id );
    
    QNetworkRequest request( url );
    request.setHeader( QNetworkRequest::ContentTypeHeader, QLatin1String( "multipart/form-data" ) );
    qDebug() << "Creating catalog::delete URL" << url;
    return Echonest::Config::instance()->nam()->post( request, QByteArray() );
}

QNetworkReply* Echonest::Catalog::list(int results, int start)
{
    QUrl url = Echonest::baseGetQuery( "catalog", "list" );
    if( results != 30 )
        url.addEncodedQueryItem( "results", QString::number( results ).toLatin1() );
    if( start > -1 )
        url.addEncodedQueryItem( "start", QString::number( start ).toLatin1() );
    
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );    
}

QNetworkReply* Echonest::Catalog::profile() const
{
    QUrl url = Echonest::baseGetQuery( "catalog", "profile" );
    if( !d->id.isEmpty() )
        url.addEncodedQueryItem( "id", d->id );
    else if( !d->name.isEmpty() )
        url.addQueryItem( QLatin1String( "name" ), d->name );
    else
        Q_ASSERT_X( false, "Catalog", "Not enough information!" );
    
    return Echonest::Config::instance()->nam()->get( QNetworkRequest( url ) );    
}

QNetworkReply* Echonest::Catalog::status(const QByteArray& ticket)
{
    return 0;
}

QNetworkReply* Echonest::Catalog::update(const Echonest::CatalogEntryList& entries) const
{
    
    return 0;
}

QNetworkReply* Echonest::Catalog::updateAndCreate(const Echonest::CatalogEntryList& entries)
{
    
    return 0;
}

QNetworkReply* Echonest::Catalog::readArtistCatalog(Echonest::Artist::ArtistInformation info, int results, int start) const
{
    
    return 0;
}

QNetworkReply* Echonest::Catalog::readSongCatalog(Echonest::Song::SongInformation info, int results, int start) const
{
    
    return 0;
}

QPair< QString, QByteArray > Echonest::Catalog::parseDelete() throw( Echonest::ParseError )
{
    QPair< QString, QByteArray > asd;
    
    return asd;
}

Echonest::Catalogs Echonest::Catalog::parseList(QNetworkReply* ) throw( Echonest::ParseError )
{
    return Echonest::Catalogs();
}

void Echonest::Catalog::parseProfile(QNetworkReply* ) throw( Echonest::ParseError )
{

}

void Echonest::Catalog::parseRead(QNetworkReply* ) throw( Echonest::ParseError )
{

}

Echonest::CatalogStatus Echonest::Catalog::parseStatus(QNetworkReply* ) throw( Echonest::ParseError )
{
    return Echonest::CatalogStatus();
}

QByteArray Echonest::Catalog::parseTicket(QNetworkReply* ) throw( Echonest::ParseError )
{
    return QByteArray();
}
