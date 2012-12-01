 /****************************************************************************************
  * Copyright (c) 2010-2012 Leo Franchi <lfranchi@kde.org>                               *
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

#include "SongTypeTest.h"

#include "Config.h"
#include "Song.h"

#include <QDebug>
#include <QNetworkReply>

void SongTypeTest::initTestCase()
{
    Echonest::Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}


void SongTypeTest::testSearch1()
{
    Echonest::Song::SearchParams params;
    //params.append( Echonest::Song::SearchParamData( Echonest::Song::Artist, QLatin1String("Dean Martin") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::SongType, QLatin1String("christmas") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::SongType, QLatin1String("live") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 30 ) );

    QNetworkReply* reply = Echonest::Song::search( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  | Echonest::SongInformation::ArtistLocation | Echonest::SongInformation::ArtistFamiliarity | Echonest::SongInformation::SongType ) );
    
    qDebug() << "Test search:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    foreach( Echonest::Song s, songs) {
      qDebug() << s;
      qDebug() << s.songTypes();
    }
    
    
}

/*
void SongTypeTest::testProfile()
{
    Echonest::Song song;
    song.setId( "SOYMZLR127CF8DD122" );

    QNetworkReply* reply = song.fetchInformation( Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistLocation ) );
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song.parseInformation( reply );

    qDebug() << song << song.artistHotttnesss() << song.artistLocation() << song.artistId() << song.artistName();
}


void SongTypeTest::testIdentify()
{
    Echonest::Song::IdentifyParams params;
    params.append( Echonest::Song::IdentifyParamData( Echonest::Song::Code, code ) );
//     params.append( Echonest::Song::IdentifyParamData( Echonest::Song::IdentifyArtist, QLatin1String( "Pink Floyd" ) ) );

    QNetworkReply* reply = Echonest::Song::identify( params );

    qDebug() << "Identifying:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::SongList songs = Echonest::Song::parseIdentify( reply );

    qDebug() << "Identified:" << songs;
    QVERIFY( songs.size() > 0 );
    QCOMPARE( songs.first().artistName(), QLatin1String( "Bon Iver" ) );
    QCOMPARE( songs.first().artistId(), QByteArray( "ARKDTAM1187FB54026" ) );
    QCOMPARE( songs.first().title(), QLatin1String( "01 Flume" ) );
    QCOMPARE( songs.first().id(), QByteArray( "SOJEVHC12A8C13C3E5" ) );
}

void SongTypeTest::testIdentifyWithData()
{
    Echonest::Song::IdentifyParams params;
    params.append( Echonest::Song::IdentifyParamData( Echonest::Song::Code, code ) );

    QNetworkReply* reply = Echonest::Song::identify( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  | Echonest::SongInformation::ArtistLocation | Echonest::SongInformation::ArtistFamiliarity ) );

//     qDebug() << "Identifying:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::SongList songs = Echonest::Song::parseIdentify( reply );

    qDebug() << "Identified:" << songs;
    QVERIFY( songs.size() > 0 );
    QCOMPARE( songs.first().artistName(), QLatin1String( "Bon Iver" ) );
    QCOMPARE( songs.first().artistId(), QByteArray( "ARKDTAM1187FB54026" ) );
    QCOMPARE( songs.first().title(), QLatin1String( "Flume" ) );
    QCOMPARE( songs.first().id(), QByteArray( "SOJEVHC12A8C13C3E5" ) );

}
*/

QTEST_MAIN(SongTypeTest)

#include "SongTypeTest.moc"
