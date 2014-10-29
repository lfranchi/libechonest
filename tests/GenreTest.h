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

#ifndef ECHONEST_GENRE_TEST_H
#define ECHONEST_GENRE_TEST_H

#include <QtTest/QtTest>

class GenreTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void testArtistsUrl();
    void testArtists();

    void testListUrl();
    void testList();

    void testProfileUrl();
    void testProfile();

    void testSearchUrl();
    void testSearch();

    void testLegacyHack();
};

#endif
