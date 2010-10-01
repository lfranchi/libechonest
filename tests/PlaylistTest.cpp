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

#include "PlaylistTest.h"

#include "Config.h"
#include "Playlist.h"

#include <QDebug>
#include <QVariant>
#include <QNetworkReply>

using namespace Echonest;

void PlaylistTest::initTestCase()
{
    Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}

void PlaylistTest::testStatic1()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "tallest man on earth" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "bon iver" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "mumford and sons" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistRadioType ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Results, 10 ) );
    
    QNetworkReply* reply = DynamicPlaylist::staticPlaylist( p );
    
    qDebug() << reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/playlist/static?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=tallest+man+on+earth&artist=bon+iver&artist=mumford+and+sons&type=artist-radio&results=10" ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    SongList songs = DynamicPlaylist::parseStaticPlaylist( reply );
    
    QVERIFY( songs.size() == 10 );
    Q_FOREACH( const Song& song, songs )
        QVERIFY( !song.id().isEmpty() );
   
}

void PlaylistTest::testStatic2()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "tallest man on earth" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "bon iver" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "mumford and sons" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::ArtistMaxFamiliarity, 0.4 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistType ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::SongInformation, QVariant::fromValue( Song::SongInformation( Song::Hotttnesss | Song::ArtistHotttnesss | Song::ArtistFamiliarity ) ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Results, 10 ) );
    
    QNetworkReply* reply = DynamicPlaylist::staticPlaylist( p );
    
    qDebug() << reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/playlist/static?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=tallest+man+on+earth&artist=bon+iver&artist=mumford+and+sons&artist_max_familiarity=0.4&type=artist&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity&results=10" ) );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    SongList songs = DynamicPlaylist::parseStaticPlaylist( reply );
    
    QVERIFY( songs.size() == 10 );
    Q_FOREACH( const Song& song, songs )
    QVERIFY( !song.id().isEmpty() );
}

void PlaylistTest::testDynamic1()
{

}

void PlaylistTest::testDynamic2()
{

}

QTEST_MAIN( PlaylistTest )

#include "PlaylistTest.moc"