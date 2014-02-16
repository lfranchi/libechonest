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


#ifndef ECHONEST_COMMONTYPES_H
#define ECHONEST_COMMONTYPES_H

namespace Echonest{
    class Artist;
    typedef QVector< Artist > Artists;
    class Genre;
    typedef QVector< Genre > Genres;
} // namespace

#endif
