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
 
#include "CatalogTest.h"

#include "Config.h"
#include "Catalog.h"

#include <QDebug>
#include <QNetworkReply>

void CatalogTest::initTestCase()
{
    Echonest::Config::instance()->setAPIKey( "N6E4NIOVYMTHNDM8J" );
}

void CatalogTest::testList()
{
    QNetworkReply* reply = Echonest::Catalog::list();
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/list?api_key=N6E4NIOVYMTHNDM8J&format=xml" ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    Echonest::Catalogs catalogs = Echonest::Catalog::parseList( reply );
    qDebug() << catalogs.size();
    qDebug() << catalogs;
    QVERIFY( !catalogs.isEmpty() );
    // QCOMPARE( catalogs.size(), 3 ) 
    
    // Now limit it to just 1, but the second one.
    reply = Echonest::Catalog::list( 1, 1 );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/list?api_key=N6E4NIOVYMTHNDM8J&format=xml&results=1&start=1" ) );
    
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    catalogs = Echonest::Catalog::parseList( reply );
    qDebug() << catalogs.size();
    QCOMPARE( catalogs.size(), 1 );
}

void CatalogTest::testProfile()
{
    Echonest::Catalog c( "CAOFUDS12BB066268E" );
    QNetworkReply* reply = c.profile();
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/profile?api_key=N6E4NIOVYMTHNDM8J&format=xml&id=CAOFUDS12BB066268E" ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    c.parseProfile( reply );
    qDebug() << c;
}

void CatalogTest::testRead()
{
    Echonest::Catalog c( "CAGPXKK12BB06F9DE9" );
    QNetworkReply* reply = c.readSongCatalog( Echonest::Song::AudioSummaryInformation | Echonest::Song::Tracks | Echonest::Song::Hotttnesss | Echonest::Song::ArtistHotttnesss | Echonest::Song::ArtistFamiliarity | Echonest::Song::ArtistLocation );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url(), QUrl( QLatin1String( "http://developer.echonest.com/api/v4/catalog/read?api_key=N6E4NIOVYMTHNDM8J&format=xml&bucket=audio_summary&bucket=tracks&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity&bucket=artist_location&id=CAGPXKK12BB06F9DE9" ) ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    c.parseRead( reply );
    qDebug() << c;
    QVERIFY( !c.songs().isEmpty() );
    QVERIFY( c.songs().at( 0 ).audioSummary().duration() > 0 );
    QVERIFY( c.songs().at( 0 ).audioSummary().danceability() > 0 );
    QVERIFY( c.songs().at( 0 ).audioSummary().energy() > 0 );
//     QVERIFY( !c.songs().at( 0 ).tracks().isEmpty() );
    QVERIFY( c.songs().at( 0 ).hotttnesss() > 0 );
    QVERIFY( !c.songs().at( 0 ).dateAdded().isNull() );
    QVERIFY( !c.songs().at( 0 ).artistId().isEmpty() );
    QVERIFY( !c.songs().at( 0 ).foreignId().isEmpty() );
    QVERIFY( c.songs().at( 0 ).artistHotttnesss() >= 0 );
    QVERIFY( c.songs().at( 0 ).artistFamiliarity() >= 0 );
    
    // test an artist catalog
    Echonest::Catalog c2( "CAOFUDS12BB066268E" );
    reply = c2.readArtistCatalog( Echonest::Artist::Audio | Echonest::Artist::Blogs | Echonest::Artist::Biographies | Echonest::Artist::Familiarity |
                                                Echonest::Artist::Hotttnesss | Echonest::Artist::Images | Echonest::Artist::News | Echonest::Artist::Reviews | 
                                                Echonest::Artist::Terms | Echonest::Artist::Urls | Echonest::Artist::Videos );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url(), QUrl( QLatin1String( "http://developer.echonest.com/api/v4/catalog/read?api_key=N6E4NIOVYMTHNDM8J&format=xml&bucket=audio&bucket=biographies&bucket=blogs&bucket=familiarity&bucket=hotttnesss&bucket=images&bucket=news&bucket=reviews&bucket=terms&bucket=urls&bucket=video&id=CAOFUDS12BB066268E" ) ) );
    
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    c2.parseRead( reply );
    qDebug() << c2;
    QVERIFY( !c2.artists().isEmpty() );
    QVERIFY( c2.artists().at( 0 ).familiarity() > 0 );
    QVERIFY( !c2.artists().at( 0 ).terms().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).biographies().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).blogs().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).name().isEmpty() );
    QVERIFY( c2.artists().at( 0 ).hotttnesss() > 0 );
    QVERIFY( !c2.artists().at( 0 ).reviews().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).videos().isEmpty() );
    QVERIFY( c2.artists().at( 0 ).lastFmUrl().isValid() );
    QVERIFY( !c2.artists().at( 0 ).news().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).images().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).audio().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).dateAdded().isNull() );
    QVERIFY( !c2.artists().at( 0 ).id().isEmpty() );
    QVERIFY( !c2.artists().at( 0 ).foreignId().isEmpty() );
}


QTEST_MAIN(CatalogTest)

#include "CatalogTest.moc"
