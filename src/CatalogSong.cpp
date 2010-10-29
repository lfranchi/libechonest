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
#include "CatalogItem_p.h"

Echonest::CatalogSong::CatalogSong()
{

}

Echonest::CatalogSong::CatalogSong(const QByteArray& id, const QString& title, const QByteArray& artistId, const QString& artistName)
    : Song(id, title, artistId, artistName)
{

}

Echonest::CatalogSong::CatalogSong(const Echonest::CatalogSong& other)
    : Song(other)
    , CatalogItem( other )
{

}

Echonest::CatalogSong& Echonest::CatalogSong::operator=(const Echonest::CatalogSong& other)
{
    Song::operator=( other );
    CatalogItem::operator=( other );
    return *this;
}

Echonest::CatalogSong::~CatalogSong()
{
}

Echonest::CatalogTypes::Type Echonest::CatalogSong::type() const
{
    return Echonest::CatalogTypes::Song;
}


QDateTime Echonest::CatalogSong::dateAdded() const
{
    return dd->date_added;
}

void Echonest::CatalogSong::setDateAdded(const QDateTime& dt)
{
    dd->date_added = dt;
}

QByteArray Echonest::CatalogSong::foreignId() const
{
    return dd->foreign_id;
}

void Echonest::CatalogSong::setForeignId(const QByteArray& id)
{
    dd->foreign_id = id;
}

QByteArray Echonest::CatalogSong::requestId() const
{
    return dd->request_id;
}

void Echonest::CatalogSong::setRequestId(const QByteArray& id)
{
    dd->request_id = id;
}

QString Echonest::CatalogSong::requestName() const
{
    return dd->request_name;
}

void Echonest::CatalogSong::setRequestName(const QString& name)
{
    dd->request_name = name;
}

int Echonest::CatalogSong::rating() const
{
    return dd->rating;
}

void Echonest::CatalogSong::setRating(int rating)
{
    dd->rating = rating;
}

int Echonest::CatalogSong::playCount() const
{
    return dd->play_count;
}

void Echonest::CatalogSong::setPlayCount(int count)
{
    dd->play_count = count;
}


