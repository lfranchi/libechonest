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


#ifndef ECHONEST_PLAYLIST_H
#define ECHONEST_PLAYLIST_H

#include "echonest_export.h"
#include "Song.h"

#include <QSharedData>
#include <QDebug>

class QNetworkReply;
class DynamicPlaylistData;

namespace Echonest{

    /**
     * The types of playlist that can be generated. Each type
     *  takes a kind of argument: artist name for Artist/ArtistRadio,
     *  and a list of descriptors for ArtistDescription. See API for more
     *  details.
     */
    namespace Playlist {
        enum Type {
            Artist,
            ArtistRadio,
            ArtistDescription
        };
    }
    
    /**
     * This encapsulates an Echo Nest dynamic playlist. It contains a playlist ID and
     *  the current song. See http://developer.echonest.com/docs/v4/playlist.html#dynamic
     *  for more information
     */
    class ECHONEST_EXPORT DynamicPlaylist
    {
        
    public:
        DynamicPlaylist();
        explicit DynamicPlaylist( const QByteArray& xmlData );
        
        QString id() const;
        void setId( const QString& id );
        
        Song currentSong() const;
        void setCurrentSong( const Song& song );
        
        /**
         * Queries The Echo Nest for the next playable song in this
         *  dynamic playlist.
         */
        Song fetchNextSong();
        
        // Generate a static playlist, or initiate a dynamic playlist
//         static DynamicPlaylist getPlaylist( Playlist::Type type )
        
    private:
        QSharedDataPointer<DynamicPlaylistData> d;
    };
    
    QDebug operator<<(QDebug d, const Echonest::DynamicPlaylist& playlist);
    
    
} // namespace
#endif
