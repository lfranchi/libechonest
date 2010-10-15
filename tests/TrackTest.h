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

#ifndef ECHONEST_TRACK_TEST_H
#define ECHONEST_TRACK_TEST_H

#include <QtTest/QtTest>

namespace Echonest {
    class Track;
}

class TrackTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    
    
    void testProfileFromMD5();
    void testProfileFromId();
    
    void testAnalyzeFromMD5();
    void testAnalyzerFromId();
    
    void testUploadLocalFile(); // slow and uploads an mp3, only enable on demand
private:    
    
    void verifyTrack1( const Echonest::Track& track );
    void verifyTrack2( const Echonest::Track& track );
};

#endif
