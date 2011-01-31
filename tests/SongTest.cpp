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


void SongTest::testSearch1()
{
    Echonest::Song::SearchParams params;
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Artist, QLatin1String("Modest Mouse") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Title, QLatin1String("Float On") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 2 ) );
    
    QNetworkReply* reply = Echonest::Song::search( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  | Echonest::SongInformation::ArtistLocation | Echonest::SongInformation::ArtistFamiliarity ) );
    qDebug() << "Test search:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    QVERIFY( !songs.isEmpty() );
    for(int i = 0; i < songs.size(); i++) {
        Echonest::Song song = songs.value(i);
        QLatin1String title = ( i == 0 ? QLatin1String( "float on" ) : QLatin1String( "night on the sun" ) );
        QVERIFY( song.title().toLower() == title );
        QVERIFY( song.artistName().toLower() == QLatin1String( "modest mouse" ) );
        QVERIFY( song.artistLocation().location.toLower() == QLatin1String( "issaquah, wa" ) );
        QVERIFY( song.hotttnesss() == -1 );
        qDebug() << song.hotttnesss() << song.artistHotttnesss() << song.artistFamiliarity() << song.artistLocation();
        
        // now fetch some more info and make sure everything is still sane
        QNetworkReply* moreInfo = song.fetchInformation( Echonest::SongInformation( Echonest::SongInformation::Hotttnesss ) );
        QEventLoop loop;
        loop.connect( moreInfo, SIGNAL(finished()), SLOT(quit()) );
        loop.exec();
        song.parseInformation( moreInfo );
        
        QVERIFY( song.title().toLower() == title );
        QVERIFY( song.artistName().toLower() == QLatin1String( "modest mouse" ) );
        QVERIFY( song.artistLocation().location.toLower() == QLatin1String( "issaquah, wa" ) );
        // make sure we got the new info
        QVERIFY( song.hotttnesss() != -1 );
        
    }
    
    params.clear();
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Artist, QLatin1String("The Tallest Man On Earth") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Title, QLatin1String("The King of Spain") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 3 ) );
    
    Echonest::SongInformation info( Echonest::SongInformation( Echonest::SongInformation::AudioSummaryInformation | Echonest::SongInformation::Tracks | Echonest::SongInformation::Hotttnesss ) );
    info.setIdSpaces( QStringList() << QLatin1String( "musicbrainz" ) << QLatin1String( "7digital" ) << QLatin1String( "playme" ) );
    reply = Echonest::Song::search( params, info);
    qDebug() << "QUERY:" << reply->url().toString();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    foreach( const Echonest::Song& song, songs ) {
//         qDebug() << "SONG  TRACKS:" << song.tracks();
        foreach( const Echonest::Track& track, song.tracks() ) {
//             qDebug() << track.catalog() << track.foreignId();
            QVERIFY( !track.catalog().isEmpty() );
            QVERIFY( !track.foreignId().isEmpty() );
        }
    }
    QVERIFY( songs.size() == 3 );
    QVERIFY( songs[ 1 ].audioSummary().danceability() > 0 );
    QVERIFY( songs[ 1 ].audioSummary().energy() > 0 );
    
    
}

void SongTest::testProfile()
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


QTEST_MAIN(SongTest)

#include "SongTest.moc"
