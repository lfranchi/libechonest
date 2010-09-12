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
 
#include "SongTest.h"

#include "Config.h"
#include "Song.h"

#include <QDebug>
#include <QNetworkReply>

void SongTest::initTestCase()
{
    Echonest::Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}


void SongTest::testSearch()
{
    Echonest::Song::SearchParams params;
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Artist, QLatin1String("Modest Mouse") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Title, QLatin1String("Three Legged Horses") ) );
    
    QNetworkReply* reply = Echonest::Song::search( params, Echonest::Song::ArtistHotttnesss );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
}

QTEST_MAIN(SongTest)

#include "SongTest.moc"