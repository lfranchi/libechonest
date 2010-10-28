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

#include "CatalogSong.h"
#include "CatalogSong_p.h"

Echonest::CatalogSong::CatalogSong()
    : d( new CatalogSongData )
{

}

Echonest::CatalogSong::CatalogSong(const QByteArray& id, const QString& title, const QByteArray& artistId, const QString& artistName)
    : Song(id, title, artistId, artistName)
    , d( new CatalogSongData )
{

}

Echonest::CatalogSong::CatalogSong(const Echonest::CatalogSong& other)
    : Song(other)
    , d( other.d )
{

}

Echonest::CatalogSong& Echonest::CatalogSong::operator=(const Echonest::CatalogSong& other)
{
    Song::operator=( other );
    d = other.d;
    return *this;
}

Echonest::CatalogSong::~CatalogSong()
{
}

QDateTime Echonest::CatalogSong::dateAdded() const
{
    return d->date_added;
}

void Echonest::CatalogSong::setDateAdded(const QDateTime& dt)
{
    d->date_added = dt;
}

QByteArray Echonest::CatalogSong::foreignId() const
{
    return d->foreign_id;
}

void Echonest::CatalogSong::setForeignId(const QByteArray& id)
{
    d->foreign_id = id;
}

QByteArray Echonest::CatalogSong::requestId() const
{
    return d->request_id;
}

void Echonest::CatalogSong::setRequestId(const QByteArray& id)
{
    d->request_id = id;
}

QString Echonest::CatalogSong::requestName() const
{
    return d->request_name;
}

void Echonest::CatalogSong::setRequestName(const QString& name)
{
    d->request_name = name;
}
