/****************************************************************************************
 * Copyright (c) 2014 Leo Franchi <lfranchi@kde.org>                                    *
 * Copyright (c) 2014 Stefan Derkits <stefan@derkits.at>                                *
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


#ifndef ECHONEST_GENRE_P_H
#define ECHONEST_GENRE_P_H

#include "Artist.h"

#include <QSharedData>
#include <QString>


namespace Echonest {
    class Genre;
}

class GenreData : public QSharedData
{
public:
    GenreData() {}
    GenreData(const GenreData& other) : QSharedData(other) {
        name = other.name;
        artists = other.artists;
        similar = other.similar;
        wikipedia_url = other.wikipedia_url;
        description = other.description;
    }

    // The following exist in all valid Genre objects
    QString name;

    //The following are populated on demand, and may not exist
    Echonest::Artists artists;

    QVector<Echonest::Genre> similar;

    QUrl wikipedia_url;

    QString description;
};

#endif
