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
#include "TypeInformation.h"

#include <QDebug>
#include <QNetworkReply>

void CatalogTest::initTestCase()
{
    Echonest::Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}

void CatalogTest::testList()
{
    QNetworkReply* reply = Echonest::Catalog::list();
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/list?api_key=JGJCRKWLXLBZIFAZB&format=xml" ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    Echonest::Catalogs catalogs = Echonest::Catalog::parseList( reply );
    qDebug() << catalogs.size();
    qDebug() << catalogs;
    QVERIFY( !catalogs.isEmpty() );
    
    // Now limit it to just 1, but the second one.
    reply = Echonest::Catalog::list( 1, 1 );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/list?api_key=JGJCRKWLXLBZIFAZB&format=xml&results=1&start=1" ) );
    
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    catalogs = Echonest::Catalog::parseList( reply );
    qDebug() << catalogs.size();
    QCOMPARE( catalogs.size(), 1 );
}

void CatalogTest::testProfile()
{
    Echonest::Catalog c( "CAWRKLJ12BF92BC7C3" );
    QNetworkReply* reply = c.profile();
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/profile?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=CAWRKLJ12BF92BC7C3" ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    c.parseProfile( reply );
    qDebug() << c;
    QEXPECT_FAIL( "", "catalog/profile returns 0 for number of catalog entries, bug filed", Abort );
    QCOMPARE( c.total(), 3 );
}

void CatalogTest::testRead()
{
    Echonest::Catalog c( "CAWRKLJ12BF92BC7C3" );
    QNetworkReply* reply = c.readSongCatalog( Echonest::SongInformation( Echonest::SongInformation::AudioSummaryInformation | Echonest::SongInformation::Tracks | Echonest::SongInformation::Hotttnesss | Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistFamiliarity | Echonest::SongInformation::ArtistLocation ) );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url(), QUrl( QLatin1String( "http://developer.echonest.com/api/v4/catalog/read?api_key=JGJCRKWLXLBZIFAZB&format=xml&bucket=audio_summary&bucket=tracks&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity&bucket=artist_location&id=CAWRKLJ12BF92BC7C3" ) ) );
    
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
    QCOMPARE( c.songs().at( 0 ).request().itemId(), QByteArray( "d951f4d6-b678-4264-8193-cd90c6b3ee4d" ) );
    QCOMPARE( c.songs().at( 0 ).request().songName(), QLatin1String( "Your Hand In Mine" ) );
    QCOMPARE( c.songs().at( 0 ).request().artistName(), QLatin1String( "Explosions in the sky" ) );
    QCOMPARE( c.songs().at( 1 ).request().itemId(), QByteArray( "1f2cc282-068b-4d0c-aa41-d0d3b1638986" ) );
    QCOMPARE( c.songs().at( 1 ).request().songName(), QLatin1String( "Your Hand In Mine" ) );
    QCOMPARE( c.songs().at( 1 ).request().artistName(), QLatin1String( "Explosions in the sky" ) );
    QCOMPARE( c.songs().at( 2 ).request().itemId(), QByteArray( "a61a4ac1-55a8-4c04-8789-5693d5d285d6" ) );
    QCOMPARE( c.songs().at( 2 ).request().songName(), QLatin1String( "Your Hand In Mine" ) );
    QCOMPARE( c.songs().at( 2 ).request().artistName(), QLatin1String( "Explosions in the sky" ) );
    QCOMPARE( c.songs().size(), 3 );
    
    foreach( const Echonest::Song& song, c.songs() ) {
        QCOMPARE( song.tracks().size(), 4 );
        QCOMPARE( song.tracks().at( 0 ).id().constData(), "TRXIFWD123E8589514" );
        QCOMPARE( song.tracks().at( 1 ).id().constData(), "TRZMJVA128F42636CE" );
        QCOMPARE( song.tracks().at( 2 ).id().constData(), "TRXKSJB128F92E8307" );
        QCOMPARE( song.tracks().at( 3 ).id().constData(), "TRWYCBR128F9325C60" );
    }
    
    // test an artist catalog
    Echonest::Catalog c2( "CAXBXBZ12BF92A9AC2" );
    reply = c2.readArtistCatalog( Echonest::ArtistInformation( Echonest::ArtistInformation::Audio | Echonest::ArtistInformation::Blogs | Echonest::ArtistInformation::Biographies | Echonest::ArtistInformation::Familiarity |
                                                Echonest::ArtistInformation::Hotttnesss | Echonest::ArtistInformation::Images | Echonest::ArtistInformation::News | Echonest::ArtistInformation::Reviews | 
                                                Echonest::ArtistInformation::Terms | Echonest::ArtistInformation::Urls | Echonest::ArtistInformation::Videos ) );
    
    qDebug() << reply->url().toString();
    QCOMPARE( reply->url(), QUrl( QLatin1String( "http://developer.echonest.com/api/v4/catalog/read?api_key=JGJCRKWLXLBZIFAZB&format=xml&bucket=audio&bucket=biographies&bucket=blogs&bucket=familiarity&bucket=hotttnesss&bucket=images&bucket=news&bucket=reviews&bucket=terms&bucket=urls&bucket=video&id=CAXBXBZ12BF92A9AC2" ) ) );
    
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
    QCOMPARE( c2.artists().at( 0 ).request().itemId(), QByteArray( "f1bc85de-de19-4cc2-a77b-475a5b4afb7b" ) );
    QCOMPARE( c2.artists().at( 0 ).request().artistName(), QLatin1String( "Balmorhea" ) );
    QCOMPARE( c2.artists().at( 1 ).request().itemId(), QByteArray( "473cb167-6459-429a-b4a2-561702753d8b" ) );
    QCOMPARE( c2.artists().at( 1 ).request().artistName(), QLatin1String( "Mono" ) );
    QCOMPARE( c2.artists().size(), 2 );
}

void CatalogTest::testStatus()
{

}

void CatalogTest::testCreateUpdateDeleteSong()
{

    QNetworkReply* reply = Echonest::Catalog::create( QLatin1String( "unittest_catalog_song_X" ), Echonest::CatalogTypes::Song );
//         
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    m_songC = Echonest::Catalog::parseCreate( reply );
    qDebug() << "CREATED NEW CATALOG:" << m_songC;
    QVERIFY( !m_songC.id().isEmpty() );
    QVERIFY( !m_songC.name().isEmpty() );
//     m_songC = Echonest::Catalog( "CAGFEYU12BFD4789A2" ); // for deleting manually a catalog
    Echonest::CatalogUpdateEntry entry;
    entry.setSongName( QLatin1String( "Your Hand In Mine" ) );
    entry.setArtistName( QLatin1String( "Explosions in the sky" ) );
//     entry.S( "fooid" );
//     entry.setFingerpring( "FINGERPRINT" );
//     entry.setRelease( QLatin1String( "FooAlbum:" ) );
//     entry.setGenre( QLatin1String( "Rock" ) );
//     entry.setRating( 5 );
//     entry.setTrackNumber( 5 );
//     entry.setDiscNumber( 1 );
//     entry.setUrl( QLatin1String( "myurl" ) );
    entry.setFavorite( true );
    entry.setAction( Echonest::CatalogTypes::Update );
    Echonest::CatalogUpdateEntries entries;
    entries << entry;
    
    reply = m_songC.update( entries );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QByteArray ticket = Echonest::Catalog::parseTicket( reply );
    qDebug() << ticket;
    
    QVERIFY( !ticket.isEmpty() );
    // now check the ticket status after 10s
    QTest::qWait( 10000 );
    reply = Echonest::Catalog::status( ticket );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::CatalogStatus cs = Echonest::Catalog::parseStatus( reply );
    qDebug() << "Catalog status:" << cs.status << cs.items_updated << cs.items;
    
    // now read the catalog
    reply = m_songC.readSongCatalog();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    m_songC.parseRead( reply );
    qDebug() << m_songC;
    QCOMPARE( m_songC.songs().size(), 1 );
    
    
}

void CatalogTest::testCreateUpdateDeleteArtist()
{
    QNetworkReply* reply = Echonest::Catalog::create( QLatin1String( "unittest_catalog_artist_X" ), Echonest::CatalogTypes::Artist );
//         
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    m_artistC = Echonest::Catalog::parseCreate( reply );
    qDebug() << "CREATED NEW ARTIST CATALOG:" << m_artistC;
    QVERIFY( !m_artistC.id().isEmpty() );
    QVERIFY( !m_artistC.name().isEmpty() );

//         c = Echonest::Catalog( "CAPRWVK12BFA1A6F17" );
    
    Echonest::CatalogUpdateEntry entry;
    entry.setArtistName( QLatin1String( "Balmorhea" ) );
    entry.setGenre( QLatin1String( "Post Rock" ) );
    entry.setAction( Echonest::CatalogTypes::Update );
    Echonest::CatalogUpdateEntry entry2;
    entry2.setArtistName( QLatin1String( "Mono" ) );
    entry2.setGenre( QLatin1String( "Post Rock" ) );
    entry2.setAction( Echonest::CatalogTypes::Update );
    Echonest::CatalogUpdateEntries entries;
    entries << entry << entry2;
    
    reply = m_artistC.update( entries );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QByteArray ticket = Echonest::Catalog::parseTicket( reply );
    qDebug() << ticket;
    
    QVERIFY( !ticket.isEmpty() );
    // now check the ticket status after 5s
    QTest::qWait( 10000 );
    reply = Echonest::Catalog::status( ticket );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::CatalogStatus cs = Echonest::Catalog::parseStatus( reply );
    qDebug() << "Catalog status:" << cs.status << cs.items_updated << cs.items;
    
    // now read the catalog
    reply = m_artistC.readSongCatalog();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    m_artistC.parseRead( reply );
    qDebug() << m_artistC;
    QCOMPARE( m_artistC.artists().size(), 2 );
    
}

void CatalogTest::cleanupTestCase()
{
    // delete the two test catalogs we created
    qDebug() << "Deleting catalogs!";
    QNetworkReply* reply = m_songC.deleteCatalog();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    reply = m_artistC.deleteCatalog();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    return;
}


QTEST_MAIN(CatalogTest)

#include "CatalogTest.moc"
