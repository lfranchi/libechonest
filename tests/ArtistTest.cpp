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
 
#include "ArtistTest.h"

#include "Config.h"
#include "Artist.h"

#include <QDebug>
#include <QNetworkReply>

using namespace Echonest;

void ArtistTest::initTestCase()
{
    Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}

void ArtistTest::testAudioUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "FooArtist" ) );
    
    QNetworkReply* reply = testArtist.fetchAudio();
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/audio?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist" ) );
    
    reply = testArtist.fetchAudio( 15 );    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/audio?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist&results=15" ) );
    
    reply = testArtist.fetchAudio( 15, 5 );    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/audio?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist&results=15&start=5" ) );
    
    testArtist.setName( QString() );
    testArtist.setId( "ARTIST_ID" );
    reply = testArtist.fetchAudio( 15, -1 );    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/audio?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=ARTIST_ID&results=15" ) );
    
    testArtist.setName( QLatin1String( "FooArtist" ) );
    reply = testArtist.fetchAudio( 100 );    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/audio?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=ARTIST_ID&results=100" ) );
}

void ArtistTest::testBiographiesUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "FooArtist" ) );

    QNetworkReply* reply = testArtist.fetchBiographies();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/biographies?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist" ) );
        
    reply = testArtist.fetchBiographies( QLatin1String( "echo-source") );
    qDebug() << "reply->url():" <<reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/biographies?api_key=JGJCRKWLXLBZIFAZB&format=xml&license=echo-source&name=FooArtist" ) );
    
    reply = testArtist.fetchBiographies();
//     qDebug() << "reply->url():" <<reply->url().toString();
//     QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/biographies?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist" ) );
    
}

void ArtistTest::testBlogsUrl()
{

}

void ArtistTest::testFamiliarityUrl()
{

}

void ArtistTest::testHotttnesssUrl()
{

}

void ArtistTest::testImagesUrl()
{

}

void ArtistTest::testNewsUrl()
{

}

void ArtistTest::testProfileUrl()
{

}

void ArtistTest::testReviewsUrl()
{

}

void ArtistTest::testSearchUrl()
{

}

void ArtistTest::testSimilarUrl()
{

}

void ArtistTest::testSongsUrl()
{

}

void ArtistTest::testTopHotttUrl()
{

}

void ArtistTest::testTermsUrl()
{

}

void ArtistTest::testTopTermsUrl()
{

}

void ArtistTest::testUrlsUrl()
{

}

void ArtistTest::testVideosUrl()
{

}

QTEST_MAIN(ArtistTest)

#include "ArtistTest.moc"
