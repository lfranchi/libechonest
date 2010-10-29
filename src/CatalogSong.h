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
#ifndef ECHONEST_CATALOG_SONG_H
#define ECHONEST_CATALOG_SONG_H

#include "Song.h"
#include "CatalogItem.h"

class CatalogSongData;
namespace Echonest {
/**
* A song that includes some additional information returned when getting a song from a catalog listing.
*/
class CatalogSong : public Song, public CatalogItem
{
public:
    CatalogSong();
    CatalogSong(const QByteArray& id, const QString& title, const QByteArray& artistId, const QString& artistName);
    CatalogSong(const Echonest::CatalogSong& other);
    virtual ~CatalogSong();
    CatalogSong& operator=( const CatalogSong& other );
    
    /**
     * The type of this item: Song.
     */
    virtual CatalogTypes::Type type() const;
    
    /**
    * The foreign id of this artist item in the catalog. e.g. CAOFUDS12BB066268E:artist:ARUI8651187B9ACF52
    * 
    * See The Echo Nest API docs for more information.
    */
    virtual QByteArray foreignId() const;
    void setForeignId( const QByteArray& id );
    
    /**
    * The request name used when this artist item was requested.
    */
    virtual QString requestName() const;
    void setRequestName( const QString& name );
    
    /**
    * The request id used when this artist was requested.
    */
    virtual QByteArray requestId() const;
    void setRequestId( const QByteArray& id );
    
    /**
     * The date and time when this song was added to the catalog
     */
    virtual QDateTime dateAdded() const;
    void setDateAdded( const QDateTime& dt );
    
    /**
     * The rating of this song.
     */
    virtual int rating() const;
    void setRating( int rating );
    
    /**
     * The play count of this song.
     */
    virtual int playCount() const;
    void setPlayCount( int count );
    
};

typedef QVector< CatalogSong > CatalogSongs;
}
#endif
