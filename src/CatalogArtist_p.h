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

#ifndef ECHONEST_CATALOG_ARTIST_P_H
#define ECHONEST_CATALOG_ARTIST_P_H

#include "Artist_p.h"

#include <QSharedData>
#include <QString>
#include <QVector>
#include <QDateTime>


class CatalogArtistData : public QSharedData
{
public:
    CatalogArtistData() {}
   
    CatalogArtistData(const CatalogArtistData& other)
    {
        request_id = other.request_id;
        request_name = other.request_name;
        foreign_id = other.foreign_id;
        date_added = other.date_added;
    }
    
    ~CatalogArtistData() {}
    
    QByteArray request_id;
    QString request_name;
    QByteArray foreign_id;
    QDateTime date_added;
};

#endif
