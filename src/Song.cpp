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

#include "Types_p.h"

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
