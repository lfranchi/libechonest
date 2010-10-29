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
    QNetworkReply* reply = c.readSongCatalog( Echonest::Song::ArtistHotttnesss  | Echonest::Song::ArtistLocation | Echonest::Song::ArtistFamiliarity );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url(), QUrl( QLatin1String( "http://developer.echonest.com/api/v4/catalog/read?api_key=N6E4NIOVYMTHNDM8J&format=xml&bucket=artist_hotttnesss&bucket=artist_familiarity&bucket=artist_location&id=CAGPXKK12BB06F9DE9" ) ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    c.parseRead( reply );
    qDebug() << c << c.songs().size() << c.songs();
}


QTEST_MAIN(CatalogTest)

#include "CatalogTest.moc"
