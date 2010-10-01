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

void ArtistTest::testAudio()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Goo Goo Dolls") );
    
    QNetworkReply* reply = testArtist.fetchAudio( 5, 2 );
    qDebug() << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.audio().size();
    QVERIFY( testArtist.audio().size() == 3 );
    
    qDebug() << testArtist.audio().at(0).artist() << testArtist.audio().at(0).date() << testArtist.audio().at(0).id() << testArtist.audio().at(0).length() << testArtist.audio().at(0).release() << 
                testArtist.audio().at(0).title() << testArtist.audio().at(0).url() << testArtist.audio().at(0).title() << testArtist.audio().at(0).link();
}

void ArtistTest::testBiographiesUrl()
{
    Artist testArtist;
    testArtist.setId( "ARH6W4X1187B99274F" ); // radiohead

    QNetworkReply* reply = testArtist.fetchBiographies();
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/biographies?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=ARH6W4X1187B99274F" ) );
        
    reply = testArtist.fetchBiographies( QLatin1String( "echo-source") );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/biographies?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=ARH6W4X1187B99274F&license=echo-source" ) );

    reply = testArtist.fetchBiographies( QLatin1String( "cc-by-sa" ), 1, 5 );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/biographies?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=ARH6W4X1187B99274F&results=1&start=5&license=cc-by-sa" ) );
}

void ArtistTest::testBiographies()
{
    Artist testArtist;
    testArtist.setId( "ARH6W4X1187B99274F" );
    
    QNetworkReply* reply = testArtist.fetchBiographies();
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.biographies().size();
    QVERIFY( testArtist.biographies().size() == 12 );
    
//     qDebug() << testArtist.biographies().at( 0 ).license().type << testArtist.biographies().at( 0 ).site() << testArtist.biographies().at( 0 ).text() << testArtist.biographies().at( 0 ).url();   
    
}


void ArtistTest::testBlogsUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "FooArtist" ) );
    testArtist.setId( "FooId" );
    
    QNetworkReply* reply = testArtist.fetchBlogs();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/blogs?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=FooId" ) );
    
    testArtist.setName( QLatin1String( "NoChange" ) );
    reply = testArtist.fetchBlogs( true, 10 );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/blogs?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=FooId&results=10&high_relevance=true" ) );
}

void ArtistTest::testBlogs()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Goo Goo Dolls") );
    
    QNetworkReply* reply = testArtist.fetchBlogs( true, 5 );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.blogs().size();
    QVERIFY( testArtist.blogs().size() == 5 );
    
    if( !testArtist.blogs().isEmpty() )
        qDebug() << testArtist.blogs().at(0).dateFound() << testArtist.blogs().at(0).datePosted() << testArtist.blogs().at(0).id() << testArtist.blogs().at(0).name() << testArtist.blogs().at(0).summary() << testArtist.blogs().at(0).url();
}


void ArtistTest::testFamiliarityUrl()
{
    Artist testArtist;
    testArtist.setId( "FooId" );
    
    QNetworkReply* reply = testArtist.fetchFamiliarity();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/familiarity?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=FooId" ) );
}

void ArtistTest::testFamiliarity()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "matchbox twenty" ) );
    
    QNetworkReply* reply = testArtist.fetchFamiliarity();
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.familiarity();
    QVERIFY( testArtist.familiarity() != -1 );
}

void ArtistTest::testHotttnesssUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "FooArtist" ) );
    
    QNetworkReply* reply = testArtist.fetchHotttnesss();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/hotttnesss?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist" ) );
}

void ArtistTest::testHotttnesss()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "matchbox twenty" ) );
    
    QNetworkReply* reply = testArtist.fetchHotttnesss();
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.hotttnesss();
    QVERIFY( testArtist.hotttnesss() != -1 );
}

void ArtistTest::testImagesUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "FooArtist" ) );
    
    QNetworkReply* reply = testArtist.fetchImages();
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/images?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist" ) );
    
    reply = testArtist.fetchImages( QLatin1String( "echo-source") );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/images?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist&license=echo-source" ) );
    
    reply = testArtist.fetchImages( QLatin1String( "cc-by-sa" ), 1, 5 );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/images?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=FooArtist&results=1&start=5&license=cc-by-sa" ) );
}

void ArtistTest::testImages()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Goo Goo Dolls" ) );
    
    QNetworkReply* reply = testArtist.fetchImages( QString(), 10 );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.images().size();
    QVERIFY( testArtist.images().size() == 10 );
    
        qDebug() << testArtist.images().at( 0 ).license().type << testArtist.images().at( 0 ).url();
}

void ArtistTest::testNewsUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "FooArtist" ) );
    testArtist.setId( "FooId" );
    
    QNetworkReply* reply = testArtist.fetchNews();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/news?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=FooId" ) );
    
    testArtist.setName( QLatin1String( "NoChange" ) );
    reply = testArtist.fetchNews( true, 10 );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/news?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=FooId&results=10&high_relevance=true" ) );
}

void ArtistTest::testNews()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Goo Goo Dolls") );
    
    QNetworkReply* reply = testArtist.fetchNews( true );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.news().size();
    //     QVERIFY( testArtist.audio().size() == 5 );
    
    if( !testArtist.news().isEmpty() )
        qDebug() << testArtist.news().at(0).dateFound() << testArtist.news().at(0).datePosted() << testArtist.news().at(0).id() << testArtist.news().at(0).name() << testArtist.news().at(0).summary() << testArtist.news().at(0).url();
}

void ArtistTest::testProfileUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "ReallyGoodArtist" ) );
    
    QNetworkReply* reply = testArtist.fetchProfile( Artist::Familiarity | Artist::Videos | Artist::Audio );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/profile?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=ReallyGoodArtist&bucket=audio&bucket=familiarity&bucket=video" ) );
    
    
    reply = testArtist.fetchProfile( Artist::Biographies | Artist::News | Artist::Reviews | Artist::Terms | Artist::Urls | Artist::MusicBrainzEntries );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/profile?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=ReallyGoodArtist&bucket=biographies&bucket=news&bucket=reviews&bucket=terms&bucket=urls&bucket=id:musicbrainz" ) );
    
    reply = testArtist.fetchProfile( Artist::Blogs | Artist::Hotttnesss | Artist::Images  | Artist::SevenDigitalEntries | Artist::PlaymeEntries );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/profile?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=ReallyGoodArtist&bucket=blogs&bucket=hotttnesss&bucket=images&bucket=id:7digital&bucket=id:playme" ) );
    
}

void ArtistTest::testProfile()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "The American Dollar" ) );
    
    QNetworkReply* reply = testArtist.fetchProfile( Artist::Audio | Artist::Hotttnesss | Artist::Familiarity | Artist::Videos );
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.audio() << testArtist.hotttnesss() << testArtist.familiarity() << testArtist.videos();
}

void ArtistTest::testReviewsUrl()
{
    Artist testArtist;
    testArtist.setId( "FooId" );
    
    QNetworkReply* reply = testArtist.fetchReviews();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/reviews?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=FooId" ) );
}

void ArtistTest::testReviews()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Balmorhea" ) );
    
    QNetworkReply* reply = testArtist.fetchReviews( 7 );  
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.reviews().size();
    QVERIFY( testArtist.reviews().size() == 7 );
    
    if( !testArtist.reviews().isEmpty() ) {
        qDebug() << testArtist.reviews().at(0).dateFound() << testArtist.reviews().at(0).dateReviewed() << testArtist.reviews().at(0).id() << testArtist.reviews().at(0).imageUrl() << testArtist.reviews().at(0).name() << testArtist.reviews().at(0).release()
            << testArtist.reviews().at(0).summary() << testArtist.reviews().at(0).url();
    }
}

void ArtistTest::testSearchUrl()
{
    Artist::SearchParams params;
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "emo^2" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "female vocalist^2" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "-happy" ) ) );
    params.append( Artist::SearchParamEntry( Artist::FuzzyMatch, true ) );
    QNetworkReply* searchResult = Artist::search( params, Artist::Familiarity | Artist::Hotttnesss );
    
    qDebug() << searchResult->url().toString();
    QVERIFY( searchResult->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/search?api_key=JGJCRKWLXLBZIFAZB&format=xml&description=emo^2&description=female+vocalist^2&description=-happy&fuzzy_match=true&limit=false&bucket=familiarity&bucket=hotttnesss" ) );
    
    params.clear();
    params.append( Artist::SearchParamEntry( Artist::MaxFamiliarity, 12.221 ) );
    params.append( Artist::SearchParamEntry( Artist::MinHotttnesss, 0.52 ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "alternative rock" ) ) );
    params.append( Artist::SearchParamEntry( Artist::FuzzyMatch, true ) );
    searchResult = Artist::search( params, Artist::Audio | Artist::Videos, true );
    QVERIFY( searchResult->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/search?api_key=JGJCRKWLXLBZIFAZB&format=xml&max_familiarity=12.221&min_hotttnesss=0.52&description=alternative+rock&fuzzy_match=true&limit=true&bucket=audio&bucket=video" ) );
    
    
}

void ArtistTest::testSearch()
{
    Artist::SearchParams params;
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "emo^2" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "female vocalist^2" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "-happy" ) ) );
    params.append( Artist::SearchParamEntry( Artist::FuzzyMatch, true ) );
    QNetworkReply* searchResult = Artist::search( params, Artist::Familiarity | Artist::Hotttnesss );
    
    QEventLoop loop;
    loop.connect( searchResult, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::Artists artists = Echonest::Artist::parseSearch( searchResult );
    
    qDebug() << artists.size();
    qDebug() << artists;
    QVERIFY( artists.size() > 0 );
    Q_FOREACH( const Artist& artist, artists ) {
        QVERIFY( artist.familiarity() >= 0 );
        QVERIFY( artist.hotttnesss() >= 0 );
    }
    
    artists.clear();
    params.clear();
    params.append( Artist::SearchParamEntry( Artist::MaxFamiliarity, .95 ) );
    params.append( Artist::SearchParamEntry( Artist::MinFamiliarity, .7 ) );
    params.append( Artist::SearchParamEntry( Artist::MinHotttnesss, 0.72 ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "alternative rock" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Description, QLatin1String( "stadium rock" ) ) );
    params.append( Artist::SearchParamEntry( Artist::FuzzyMatch, true ) );
    searchResult = Artist::search( params, Artist::Familiarity | Artist::Hotttnesss | Artist::News | Artist::Blogs | Artist::Audio );
    
    QEventLoop loop2;
    loop2.connect( searchResult, SIGNAL(finished()), SLOT(quit()) );
    loop2.exec();
    artists = Echonest::Artist::parseSearch( searchResult );
    
    qDebug() << artists.size();
    qDebug() << artists;
    QVERIFY( artists.size() > 0 );
    Q_FOREACH( const Artist& artist, artists ) {
        QVERIFY( artist.familiarity() >= 0 );
        QVERIFY( artist.hotttnesss() >= 0 );
        QVERIFY( artist.news().size() > 0 );
        QVERIFY( artist.blogs().size() > 0 );
        QVERIFY( artist.audio().size() > 0 );
    }
}

void ArtistTest::testSimilarUrl()
{
    Artist::SearchParams params;
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "The Beatles" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Rilo Kiley" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Queen" ) ) );
    params.append( Artist::SearchParamEntry( Artist::MinHotttnesss, 0.5 ) );
    
    QNetworkReply* reply = Artist::fetchSimilar( params, Artist::Hotttnesss | Artist::Familiarity | Artist::Audio );
    
    qDebug() << reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/similar?api_key=JGJCRKWLXLBZIFAZB&format=xml&bucket=audio&bucket=familiarity&bucket=hotttnesss&name=The+Beatles&name=Rilo+Kiley&name=Queen&min_hotttnesss=0.5" ) );

    params.clear();
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Devo" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "The New Pornographers" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Lady Gaga" ) ) );
    params.append( Artist::SearchParamEntry( Artist::MinFamiliarity, 0.5 ) );
    
    reply = Artist::fetchSimilar( params, Artist::Biographies | Artist::News | Artist::Audio, 10 );
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/similar?api_key=JGJCRKWLXLBZIFAZB&format=xml&bucket=audio&bucket=biographies&bucket=news&results=10&name=Devo&name=The+New+Pornographers&name=Lady+Gaga&min_familiarity=0.5" ) );
}

void ArtistTest::testSimilar()
{
    Artist::SearchParams params;
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "The Beatles" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Rilo Kiley" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Queen" ) ) );
    params.append( Artist::SearchParamEntry( Artist::MinHotttnesss, 0.5 ) );
    
    QNetworkReply* reply = Artist::fetchSimilar( params, Artist::Hotttnesss | Artist::Familiarity | Artist::Audio );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::Artists artists = Echonest::Artist::parseSimilar( reply );
    
    qDebug() << artists.size();
    qDebug() << artists;
    QVERIFY( artists.size() > 0 );
    Q_FOREACH( const Artist& artist, artists ) {
        QVERIFY( artist.familiarity() >= 0 );
        QVERIFY( artist.hotttnesss() >= 0 );
        QVERIFY( artist.audio().size() > 0 );
    }
    
    artists.clear();
    params.clear();
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Devo" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "The New Pornographers" ) ) );
    params.append( Artist::SearchParamEntry( Artist::Name, QLatin1String( "Lady Gaga" ) ) );
    params.append( Artist::SearchParamEntry( Artist::MinFamiliarity, 0.5 ) );
    
    reply = Artist::fetchSimilar( params, Artist::Biographies | Artist::News | Artist::Videos, 10 );

    QEventLoop loop2;
    loop2.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop2.exec();
    artists = Echonest::Artist::parseSimilar( reply );
    
    qDebug() << artists.size();
    qDebug() << artists;
    QVERIFY( artists.size() ==  10 );
    Q_FOREACH( const Artist& artist, artists ) {
        QVERIFY( artist.biographies().size() >= 0 );
        QVERIFY( artist.news().size() >= 0 );
        QVERIFY( artist.videos().size() > 0 );
    }
}


void ArtistTest::testSongsUrl()
{
    Artist testArtist;
    testArtist.setId( "DummyDudeID" );
    
    QNetworkReply* reply = testArtist.fetchSongs();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/songs?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=DummyDudeID" ) );
}

void ArtistTest::testSongs()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Balmorhea" ) );
    
    QNetworkReply* reply = testArtist.fetchSongs();  
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    qDebug() << testArtist.songs().size();
    QVERIFY( testArtist.songs().size() > 0 );
    
    qDebug() << testArtist.songs();
}

void ArtistTest::testTopHotttUrl()
{
    QNetworkReply* reply = Artist::topHottt( Artist::Hotttnesss );
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/top_hottt?api_key=JGJCRKWLXLBZIFAZB&format=xml&bucket=hotttnesss&limit=false" ) );
}

void ArtistTest::testTerms()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Balmorhea" ) );
    
    QNetworkReply* reply = testArtist.fetchTerms();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    QVERIFY( testArtist.terms().size() > 0 );
    
    qDebug() << testArtist.terms();
    reply = testArtist.fetchTerms( Echonest::Artist::Weight );
    QEventLoop loop2;
    loop2.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop2.exec();
    testArtist.parseProfile( reply );
    
    QVERIFY( testArtist.terms().size() > 0 );
    
    
    qDebug() << testArtist.terms();
}

void ArtistTest::testTermsUrl()
{
    Artist testArtist;
    testArtist.setId( "DummyDudeID" );
    
    QNetworkReply* reply = testArtist.fetchTerms();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/terms?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=DummyDudeID&sort=frequency" ) );
    
    reply = testArtist.fetchTerms( Echonest::Artist::Weight );
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/terms?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=DummyDudeID&sort=weight" ) );
}

void ArtistTest::testTopHottt()
{
    QNetworkReply* reply = Artist::topHottt();
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    Artists artists = Artist::parseTopHottt( reply );
    
    qDebug() << artists.size() << artists;
    QVERIFY( artists.size() > 0 );
    
    reply = Artist::topHottt( Artist::Hotttnesss | Artist::Familiarity, 20 );
    
    QEventLoop loop2;
    loop2.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop2.exec();
    
    artists = Artist::parseTopHottt( reply );
    
    qDebug() << artists.size() << artists;
    QVERIFY( artists.size() == 20 );
    
    Q_FOREACH( const Artist& artist, artists ) {
        QVERIFY( artist.familiarity() > 0 );
        QVERIFY( artist.hotttnesss() > 0 );
    }
    
}

void ArtistTest::testTopTermsUrl()
{
    
    QNetworkReply* reply = Artist::topTerms( 5 );
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/top_terms?api_key=JGJCRKWLXLBZIFAZB&format=xml&results=5" ) );
}

void ArtistTest::testTopTerms()
{
    QNetworkReply* reply = Artist::topTerms( 5 );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    TermList terms = Artist::parseTopTerms( reply );
    
    qDebug() << terms.size() << terms;
    QVERIFY( terms.size() == 5 );
}

void ArtistTest::testUrlsUrl()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Goo Goo Dolls" ) );
    
    QNetworkReply* reply = testArtist.fetchUrls();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/urls?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=Goo+Goo+Dolls" ) );
}

void ArtistTest::testUrls()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Balmorhea" ) );
    
    QNetworkReply* reply = testArtist.fetchUrls();

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    QVERIFY( !testArtist.lastFmUrl().isEmpty() );
    QVERIFY( !testArtist.aolMusicUrl().isEmpty() );
    QVERIFY( !testArtist.myspaceUrl().isEmpty() );
    QVERIFY( !testArtist.amazonUrl().isEmpty() );
    QVERIFY( !testArtist.itunesUrl().isEmpty() );
    QVERIFY( !testArtist.musicbrainzUrl().isEmpty() );
}

void ArtistTest::testVideosUrl()
{
    Artist testArtist;
    testArtist.setId( "DummyDudeID" );
    
    QNetworkReply* reply = testArtist.fetchVideo();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/video?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=DummyDudeID" ) );
    
    testArtist.setId( QByteArray() );
    testArtist.setName( QLatin1String( "OHAI ARTIST" ) );
    reply = testArtist.fetchVideo( 10, 5 );
    
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/artist/video?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=OHAI+ARTIST&results=10&start=5" ) );
}

void ArtistTest::testVideos()
{
    Artist testArtist;
    testArtist.setName( QLatin1String( "Balmorhea" ) );
    
    QNetworkReply* reply = testArtist.fetchVideo();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    testArtist.parseProfile( reply );
    
    QVERIFY( testArtist.videos().size() > 0 );
    
    qDebug() << testArtist.videos();
    
    reply = testArtist.fetchVideo( 5, 2 );
    QEventLoop loop2;
    loop2.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop2.exec();
    testArtist.parseProfile( reply );
    
    QVERIFY( testArtist.videos().size() > 0 );
    qDebug() << testArtist.videos();
}


QTEST_MAIN(ArtistTest)

#include "ArtistTest.moc"
