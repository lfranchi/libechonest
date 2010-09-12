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

#include "Playlist.h"
#include "Playlist_p.h"

Echonest::DynamicPlaylist::DynamicPlaylist()
    : d( new DynamicPlaylistData )
{

}

Echonest::DynamicPlaylist::DynamicPlaylist(const QByteArray& xmlData)
    : d( new DynamicPlaylistData )
{
    // parse xml
}

QString Echonest::DynamicPlaylist::id() const
{
    return d->sessionId;
}

void Echonest::DynamicPlaylist::setId(const QString& id)
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

Echonest::Song Echonest::DynamicPlaylist::fetchNextSong()
{

}

QDebug Echonest::operator<<(QDebug d, const Echonest::DynamicPlaylist& playlist)
{
    d << QString::fromLatin1( "DynamicPlaylist(%1, %2)" ).arg( playlist.id(), playlist.currentSong().toString() );
    return d.maybeSpace();
}
