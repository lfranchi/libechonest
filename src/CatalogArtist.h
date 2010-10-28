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
#ifndef ECHONEST_CATALOG_ARTIST_H
#define ECHONEST_CATALOG_ARTIST_H

#include "Artist.h"

class CatalogArtistData;
namespace Echonest {
/**
 * An artist that includes some additional information returned when getting an artist from a catalog listing.
 */
class CatalogArtist : public Artist
{
public:
    CatalogArtist();
    explicit CatalogArtist(const QString& name);
    CatalogArtist(const QByteArray& id, const QString& name);
    CatalogArtist(const Echonest::CatalogArtist& other);
    ~CatalogArtist();
    CatalogArtist& operator=( const CatalogArtist& other );
    
    /**
     * The foreign id of this artist item in the catalog. e.g. CAOFUDS12BB066268E:artist:ARUI8651187B9ACF52
     * 
     * See The Echo Nest API docs for more information.
     */
    QByteArray foreignId() const;
    void setForeignId( const QByteArray& id );
    
    /**
     * The request name used when this artist item was requested.
     */
    QString requestName() const;
    void setRequestName( const QString& name );
    
    /**
     * The request id used when this artist was requested.
     */
    QByteArray requestId() const;
    void setRequestId( const QByteArray& id );
    
    /**
     * The date and time when this artist was added to the catalog
     */
    QDateTime dateAdded() const;
    void setDateAdded( const QDateTime& dt );
    
private:
    QSharedDataPointer<CatalogArtistData> d;
};

typedef QVector< CatalogArtist > CatalogArtists;

}
#endif
