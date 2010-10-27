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

#ifndef ECHONEST_CATALOG_H
#define ECHONEST_CATALOG_H

#include "CatalogEntry.h"
#include "echonest_export.h"
#include "Util.h"

#include <QSharedDataPointer>
#include <QString>

class QNetworkReply;
class CatalogData;

namespace Echonest
{

class ECHONEST_EXPORT Catalog
{
public:    
    Catalog();
    explicit Catalog( const QByteArray& id );
    Catalog( const Catalog& );
    ~Catalog();
    Catalog& operator=( const Catalog& );
    
    /**
     * Update this catalog with new items, or removing existing items. Call parseUpdate() 
     *  to handle the result.
     * 
     * See more information about this api call at http://developer.echonest.com/docs/v4/catalog.html#update
    */
    QNetworkReply* update( const CatalogEntryList& entries );
    
    /**
     * Create a new catalog with the given name and type. 
     * 
     * Parse the finished QNetworkReply with parseCreate()
     * 
     *  \param name The name of the catalog to create
     *  \param type The type of the catalog to create
     */
    static QNetworkReply* create( const QString& name, CatalogTypes::Type type );
    
    /**
     * Creates a new catalog with the given items.
     * See more information about this api call at http://developer.echonest.com/docs/v4/catalog.html#update
     * 
     * \param entries The list of entries to populate the catalog with.
     * 
     */
    static QNetworkReply* updateAndCreate( const CatalogEntryList& entries );
    
    
private:
    QSharedDataPointer< CatalogData > d;
};
    
}

#endif
