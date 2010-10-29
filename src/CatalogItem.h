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

#ifndef ECHONEST_CATALOG_ITEM_H
#define ECHONEST_CATALOG_ITEM_H

#include "echonest_export.h"
#include "Util.h"
#include <QSharedPointer>
#include <QDateTime>

class CatalogItemData;

namespace Echonest {
    
/**
* Since catalog items can be artists or songs, and we don't know sometimes until after we parse them,
*  but we need to gather a list of them. A poor man's traits class? A rich man's interface? Far from either.
*/

class ECHONEST_EXPORT CatalogItem
{
public:
    CatalogItem();
    CatalogItem( const CatalogItem& other );
    CatalogItem& operator=( const CatalogItem& other );
    virtual ~CatalogItem();
    
    /**
     * The type of this item.
     */
    virtual Echonest::CatalogTypes::Type type() const = 0;    
    
    /**
     * The foreign id of this artist item in the catalog. e.g. CAOFUDS12BB066268E:artist:ARUI8651187B9ACF52
     * 
     * See The Echo Nest API docs for more information.
     */
    virtual QByteArray foreignId() const = 0;
    
    /**
     * The request name used when this item was requested.
     */
    virtual QString requestName() const = 0;
    
    /**
     * The request id used when this item was requested.
     */
    virtual QByteArray requestId() const = 0;
    
    /**
     * The date and time when this item was added to the catalog
     */
    virtual QDateTime dateAdded() const = 0;
    
    /**
     * The rating of this item.
     */
    virtual int rating() const = 0;
    
    /**
     * The play count of this item.
     */
    virtual int playCount() const = 0;
    
protected:
    QSharedPointer<CatalogItemData> dd;
};

typedef QVector< CatalogItem > CatalogItems;
}

#endif
