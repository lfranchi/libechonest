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
#include "CatalogEntry.h"
#include "CatalogEntry_p.h"


Echonest::CatalogEntry::CatalogEntry( CatalogTypes::Action action )
    : d( new CatalogEntryData )
{
    d->action = action;
}

Echonest::CatalogEntry::CatalogEntry( const Echonest::CatalogEntry& other )
    : d( other.d )
{

}

Echonest::CatalogEntry::~CatalogEntry()
{
}

Echonest::CatalogEntry& Echonest::CatalogEntry::operator=(const Echonest::CatalogEntry& other)
{
    d = other.d;
    return *this;
}

Echonest::CatalogTypes::Action Echonest::CatalogEntry::action() const
{
    return d->action;
}

void Echonest::CatalogEntry::setAction(Echonest::CatalogTypes::Action action)
{
    d->action = action;
}

QByteArray Echonest::CatalogEntry::artistId() const
{
    return d->artist_id;
}

void Echonest::CatalogEntry::setArtistId(const QByteArray& id)
{
    d->artist_id = id;
}

QString Echonest::CatalogEntry::artistName() const
{
    return d->artist_name;
}

void Echonest::CatalogEntry::setArtistName(const QString& name)
{
    d->artist_name = name;
}

bool Echonest::CatalogEntry::banned() const
{
    return d->banned;
}

void Echonest::CatalogEntry::setBanned(bool banned)
{
    d->bannedSet = true;
    d->banned = banned;
}

int Echonest::CatalogEntry::discNumber() const
{
    return d->disc_number;
}

void Echonest::CatalogEntry::setDiscNumber(int disc)
{
    d->disc_number = disc;
}

bool Echonest::CatalogEntry::favorite() const
{
    return d->favorite;
}

void Echonest::CatalogEntry::setFavorite(bool fav)
{
    d->favoriteSet = true;
    d->favorite = fav;
}

QString Echonest::CatalogEntry::genre() const
{
    return d->genre;
}

void Echonest::CatalogEntry::setGenre(const QString& genre)
{
    d->genre = genre;
}

int Echonest::CatalogEntry::playCount() const
{
    return d->play_count;
}

void Echonest::CatalogEntry::setPlayCount(int playCount)
{
    d->play_count = playCount;
}

int Echonest::CatalogEntry::rating() const
{
    return d->rating;
}

void Echonest::CatalogEntry::setRating(int rating)
{
    d->rating = rating;
}

QString Echonest::CatalogEntry::release() const
{
    return d->release;
}

void Echonest::CatalogEntry::setRelease(const QString& release)
{
    d->release = release;
}

int Echonest::CatalogEntry::skipCount() const
{
    return d->skip_count;
}

void Echonest::CatalogEntry::setSkipCount(int skipCount)
{
    d->skip_count = skipCount;
}

QByteArray Echonest::CatalogEntry::songId() const
{
    return d->song_id;
}

void Echonest::CatalogEntry::setSongId(const QByteArray& id)
{
    d->song_id = id;
}

QString Echonest::CatalogEntry::songName() const
{
    return d->song_name;
}

void Echonest::CatalogEntry::setSongName(const QString& name)
{
    d->song_name = name;
}

int Echonest::CatalogEntry::trackNumber() const
{
    return d->track_number;
}

void Echonest::CatalogEntry::setTrackNumber(int trackNum)
{
    d->track_number = trackNum;
}

QString Echonest::CatalogEntry::url() const
{
    return d->url;
}

void Echonest::CatalogEntry::setUrl(const QString& url)
{
    d->url = url;
}