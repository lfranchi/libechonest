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

#include "CatalogArtist.h"
#include "CatalogArtist_p.h"

Echonest::CatalogArtist::CatalogArtist()
    : d( new CatalogArtistData )
{

}

Echonest::CatalogArtist::CatalogArtist(const QString& name)
    : Artist( name )
    , d( new CatalogArtistData )
{

}

Echonest::CatalogArtist::CatalogArtist(const QByteArray& id, const QString& name)
    : Artist(id, name)
    , d( new CatalogArtistData )
{

}

Echonest::CatalogArtist::CatalogArtist(const Echonest::CatalogArtist& other)
    : Artist( other )
    , d( other.d )
{

}

Echonest::CatalogArtist::~CatalogArtist()
{

}

Echonest::CatalogArtist& Echonest::CatalogArtist::operator=(const Echonest::CatalogArtist& other)
{
    Artist::operator=( other );
    d = other.d;
    return *this;
}

QDateTime Echonest::CatalogArtist::dateAdded() const
{
    return d->date_added;
}

void Echonest::CatalogArtist::setDateAdded(const QDateTime& dt)
{
    d->date_added = dt;
}

QByteArray Echonest::CatalogArtist::foreignId() const
{
    return d->foreign_id;
}

void Echonest::CatalogArtist::setForeignId(const QByteArray& id)
{
    d->foreign_id = id;
}

QByteArray Echonest::CatalogArtist::requestId() const
{
    return d->request_id;
}

void Echonest::CatalogArtist::setRequestId(const QByteArray& id)
{
    d->request_id = id;
}

QString Echonest::CatalogArtist::requestName() const
{
    return d->request_name;
}

void Echonest::CatalogArtist::setRequestName(const QString& name)
{
    d->request_name = name;
}
