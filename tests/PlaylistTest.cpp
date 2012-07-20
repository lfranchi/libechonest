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

#include "PlaylistTest.h"

#include "Config.h"
#include "Playlist.h"

#include <QDebug>
#include <QtXml/QDomDocument>
#include <QVariant>
#include <QNetworkReply>
#include <QtNetwork/QNetworkReply>

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
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "Florence + The Machine" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::ArtistMaxFamiliarity, 0.4 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::MinDanceability, 0.7 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistType ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::SongInformation, QVariant::fromValue( Echonest::SongInformation( Echonest::SongInformation::Hotttnesss | Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistFamiliarity ) ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Results, 4 ) );

    QNetworkReply* reply = DynamicPlaylist::staticPlaylist( p );

    qDebug() << reply->url().toEncoded();
    QCOMPARE( QLatin1String( reply->url().toEncoded() ), QLatin1String( "http://developer.echonest.com/api/v4/playlist/static?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=tallest+man+on+earth&artist=bon+iver&artist=mumford+and+sons&artist=Florence+%2B+The+Machine&artist_max_familiarity=0.4&min_danceability=0.7&type=artist&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity&results=4" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    SongList songs = DynamicPlaylist::parseStaticPlaylist( reply );

//     qDebug() << "Got songs;" << songs;
    QVERIFY( songs.size() > 1 );
    Q_FOREACH( const Song& song, songs ) {
        QVERIFY( !song.id().isEmpty() );
    }

    p.clear();
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Description, QLatin1String( "70s" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Description, QLatin1String( "folk^2" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::ArtistMinFamiliarity, 0.4 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::MaxTempo, 100 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Mode, 0 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistDescriptionType ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Style, QLatin1String( "acoustic" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::SongInformation, QVariant::fromValue( Echonest::SongInformation( Echonest::SongInformation::AudioSummaryInformation | Echonest::SongInformation::Hotttnesss | Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistFamiliarity ) ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Results, 7 ) );

    reply = DynamicPlaylist::staticPlaylist( p );

//     qDebug() << reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/playlist/static?api_key=JGJCRKWLXLBZIFAZB&format=xml&description=70s&description=folk^2&artist_min_familiarity=0.4&max_tempo=100&mode=0&type=artist-description&style=acoustic&bucket=audio_summary&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity&results=7" ) );

    QEventLoop loop2;
    loop2.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop2.exec();
    songs = DynamicPlaylist::parseStaticPlaylist( reply );

    QVERIFY( songs.size() == 7 );
    Q_FOREACH( const Song& song, songs ) {
        QVERIFY( !song.id().isEmpty() );
//         qDebug() << song << song.audioSummary();
        QVERIFY( song.audioSummary().duration() > 0 );
    }

}

void PlaylistTest::testStaticXSPF()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "balmorhea" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "tallest man on earth" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Artist, QLatin1String( "explosions in the sky" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::ArtistMaxFamiliarity, 0.4 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Format, QLatin1String( "xspf" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::MaxDanceability, 0.5 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistType ) );
    Echonest::SongInformation info( Echonest::SongInformation::Hotttnesss | Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistFamiliarity | Echonest::SongInformation::Tracks );
    info.setIdSpaces( QStringList() << QLatin1String( "musicbrainz" ) << QLatin1String( "7digital" ) << QLatin1String( "playme" ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::SongInformation, QVariant::fromValue( info ) )  );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Limit, true ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Results, 40 ) );

    QNetworkReply* reply = DynamicPlaylist::staticPlaylist( p );

    qDebug() << reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/playlist/static?api_key=JGJCRKWLXLBZIFAZB&artist=balmorhea&artist=tallest+man+on+earth&artist=explosions+in+the+sky&artist_max_familiarity=0.4&format=xspf&max_danceability=0.5&type=artist&bucket=tracks&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity&bucket=id:musicbrainz&bucket=id:7digital&bucket=id:playme&limit=true&results=40" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    QByteArray xspf = DynamicPlaylist::parseXSPFPlaylist( reply );

    // verify it's valid
    QDomDocument doc;
    QVERIFY( doc.setContent( xspf ) );
    QVERIFY( !xspf.isEmpty() );

}


void PlaylistTest::testDynamic1()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "tallest man on earth" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "fleet foxes" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "johnny cash" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "crosby, stills, nash and young" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistRadioType ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMinHotttnesss, .6 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMaxFamiliarity, .4 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Mood, QLatin1String( "sad" ) ) );

    DynamicPlaylist playlist;
    QNetworkReply* reply = playlist.create( p );

    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/playlist/dynamic/create?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=tallest+man+on+earth&artist=fleet+foxes&artist=johnny+cash&artist=crosby,+stills,+nash+and+young&type=artist-radio&artist_min_hotttnesss=0.6&artist_max_familiarity=0.4&mood=sad" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseCreate( reply );

    reply = playlist.next( 1 );

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    Song song = playlist.parseNext( reply ).first.first();
//     qDebug() << "next:" << song;
    
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    reply = playlist.next( 1 );

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song = playlist.parseNext( reply ).first.first();

//     qDebug() << "next:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    reply = playlist.next( 1 );

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song = playlist.parseNext( reply ).first.first();

//     qDebug() << "next:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );
}

void PlaylistTest::testDynamic2()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "pink floyd^-1" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "the who" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "queen" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "led zeppelin^2" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "-the beatles" ) ) ); //exclude
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistType ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMinHotttnesss, .7 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMaxFamiliarity, .3 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::MinLoudness, -10 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Mode, 1 ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::SongInformation, QVariant::fromValue( Echonest::SongInformation( Echonest::SongInformation::AudioSummaryInformation | Echonest::SongInformation::Hotttnesss | Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistFamiliarity ) ) ) );

    DynamicPlaylist playlist;
    QNetworkReply* reply = playlist.create( p );

    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/playlist/dynamic/create?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=pink+floyd^-1&artist=the+who&artist=queen&artist=led+zeppelin^2&artist=-the+beatles&type=artist&artist_min_hotttnesss=0.7&artist_max_familiarity=0.3&min_loudness=-10&mode=1&bucket=audio_summary&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseCreate( reply );

    reply = playlist.next( 1 );

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::Song song = playlist.parseNext( reply ).first.first();
    
//     qDebug() << "next:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    // GET NEXT
    reply = playlist.next( 1 );

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song = playlist.parseNext( reply ).first.first();

//     qDebug() << "next:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    // GET NEXT
    reply = playlist.next( 1 );

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song = playlist.parseNext( reply ).first.first();

//     qDebug() << "next:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    // GET NEXT
    DynamicPlaylist::PlaylistParams steering;
    steering.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::TargetEnergy, QLatin1String( ".8" ) ) );
    steering.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMinFamiliarity, QLatin1String( ".5" ) ) );
    
    reply = playlist.steer( steering );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseSteer( reply );
    
    reply = playlist.next( 1 );
//     qDebug() << "Control URL:" << reply->url().toString();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song = playlist.parseNext( reply ).first.first();
//     qDebug() << "next steered:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    // GET NEXT
    steering.clear();
    steering.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::TargetLoudness, QLatin1String( ".9" ) ) );
    steering.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::MoreLikeThis, QLatin1String( "last" ) ) );
    
    reply = playlist.steer( steering );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseSteer( reply );

    playlist.next();
    
    reply = playlist.next( 1 );
//     qDebug() << "Control URL:" << reply->url().toString();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song = playlist.parseNext( reply ).first.first();
//     qDebug() << "next steered:" << song;
    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );

    // GET INFO TODO
    /*reply = playlist.fetchSessionInfo();
    qDebug() << "session info URL:" << reply->url().toString();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::SessionInfo info = playlist.parseSessionInfo( reply );
    QVERIFY( !info.banned_artists.isEmpty() );
    QVERIFY( !info.banned_songs.isEmpty() );
    QVERIFY( !info.banned_songs.at( 0 ).artist_id.isEmpty() );
    QVERIFY( !info.banned_songs.at( 0 ).artist_name.isEmpty() );
    QVERIFY( !info.banned_songs.at( 0 ).id.isEmpty() );
    QVERIFY( !info.banned_songs.at( 0 ).title.isEmpty() );
    QVERIFY( !info.skipped_songs.isEmpty() );
    QVERIFY( !info.skipped_songs.at( 0 ).artist_id.isEmpty() );
    QVERIFY( !info.skipped_songs.at( 0 ).artist_name.isEmpty() );
    QVERIFY( !info.skipped_songs.at( 0 ).id.isEmpty() );
    QVERIFY( !info.skipped_songs.at( 0 ).title.isEmpty() );
    QVERIFY( !info.rated_songs.isEmpty() );
    QVERIFY( !info.rated_songs.at( 0 ).artist_id.isEmpty() );
    QVERIFY( !info.rated_songs.at( 0 ).artist_name.isEmpty() );
    QVERIFY( !info.rated_songs.at( 0 ).id.isEmpty() );
    QVERIFY( !info.rated_songs.at( 0 ).title.isEmpty() );
    QVERIFY( !info.history.isEmpty() );
    QVERIFY( !info.history.at( 0 ).artist_id.isEmpty() );
    QVERIFY( !info.history.at( 0 ).artist_name.isEmpty() );
    QVERIFY( !info.history.at( 0 ).id.isEmpty() );
    QVERIFY( !info.history.at( 0 ).title.isEmpty() );
    QVERIFY( !info.playlist_type.isEmpty() );
    QVERIFY( !info.rules.isEmpty() );
    QVERIFY( !info.session_id.isEmpty() );

    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );*/
    QByteArray oldId = playlist.sessionId();
    // now reset it
    p.clear();
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistRadioType ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "pink floyd" ) ) );
    reply = playlist.create( p );
    qDebug() << reply->url().toString();

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseCreate( reply );

    reply = playlist.next();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    song = playlist.parseNext( reply ).first.first();
//     qDebug() << "new:" << song << song.artistFamiliarity() << song.artistHotttnesss();

    QVERIFY( !song.id().isEmpty() );
    QVERIFY( !song.title().isEmpty() );
    QVERIFY( song.artistHotttnesss() == -1 ); // make sure we are in a new playlist, and we didn't ask for this info so it shouldn't be there
    QVERIFY( song.artistFamiliarity() == -1 ); // make sure we are in a new playlist, and we didn't ask for this info so it shouldn't be there

    reply = playlist.deleteSession();

    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    playlist.parseDeleteSession(reply);
    Q_ASSERT(playlist.sessionId().isEmpty());
    
}

void PlaylistTest::testNewDynamicAPI()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "frightened rabbit" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "wilco" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "the tallest man on earth" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "noah and the whale" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMaxFamiliarity, QLatin1String( ".4" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Key, QLatin1String( "3" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistRadioType ) );

    DynamicPlaylist playlist;
    QNetworkReply* reply = playlist.create( p );

//     qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/playlist/dynamic/create?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=frightened+rabbit&artist=wilco&artist=the+tallest+man+on+earth&artist=noah+and+the+whale&artist_max_familiarity=.4&key=3&type=artist-radio" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseCreate( reply );

    reply = playlist.next( 2 );

//     qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QString( QLatin1String( "http://developer.echonest.com/api/v4/playlist/dynamic/next?api_key=JGJCRKWLXLBZIFAZB&format=xml&session_id=%1&results=2&lookahead=0" ) ).arg( QString::fromLatin1( playlist.sessionId() ) ) );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    QPair< SongList, SongList > ret;
    ret = playlist.parseNext( reply );

    QCOMPARE( ret.first.size(), 2 );
    QCOMPARE( ret.second.size(), 0 );

    QVERIFY( !ret.first.at( 0 ).id().isNull() );
    QVERIFY( !ret.first.at( 0 ).title().isNull() );
    QVERIFY( !ret.first.at( 1 ).id().isNull() );
    QVERIFY( !ret.first.at( 1 ).title().isNull() );

    DynamicPlaylist::DynamicFeedback feedback;
    feedback.append( DynamicPlaylist::DynamicFeedbackParamData( DynamicPlaylist::FavoriteArtist, "last" ) );
    feedback.append( DynamicPlaylist::DynamicFeedbackParamData( DynamicPlaylist::FavoriteSong, "last" ) );
    reply = playlist.feedback( feedback );

//     qDebug() << reply->url().toString();
    QString u = QString::fromUtf8( "http://developer.echonest.com/api/v4/playlist/dynamic/feedback?api_key=JGJCRKWLXLBZIFAZB&format=xml&session_id=%1&favorite_artist=last&favorite_song=last" );
    QCOMPARE( reply->url().toString(), u.arg( QString::fromUtf8( playlist.sessionId() ) ) );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseFeedback( reply );

    DynamicPlaylist::PlaylistParams steering;
    steering.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::MoreLikeThis, QLatin1String( "SONRAMP13775DE8214^4" ) ) );
    steering.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Mood, QLatin1String( "happy^2" ) ) );

    reply = playlist.steer( steering );

//     qDebug() << reply->url().toString();
    u = QString::fromUtf8( "http://developer.echonest.com/api/v4/playlist/dynamic/steer?api_key=JGJCRKWLXLBZIFAZB&format=xml&session_id=%1&more_like_this=SONRAMP13775DE8214^4&mood=happy^2" );
    QCOMPARE( reply->url().toString(), u.arg( QString::fromUtf8( playlist.sessionId() ) ) );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    playlist.parseSteer( reply );

    reply = playlist.next( 3, 3 );

//     qDebug() << reply->url().toString();
    u = QString::fromUtf8( "http://developer.echonest.com/api/v4/playlist/dynamic/next?api_key=JGJCRKWLXLBZIFAZB&format=xml&session_id=%1&results=3&lookahead=3" );
    QCOMPARE( reply->url().toString(), u.arg( QString::fromUtf8( playlist.sessionId() ) ) );
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    ret = playlist.parseNext( reply );

    QCOMPARE( ret.first.size(), 3 );
    QCOMPARE( ret.second.size(), 3 );

    QVERIFY( !ret.first.at( 0 ).id().isNull() );
    QVERIFY( !ret.first.at( 0 ).title().isNull() );
    QVERIFY( !ret.first.at( 1 ).id().isNull() );
    QVERIFY( !ret.first.at( 1 ).title().isNull() );
    QVERIFY( !ret.first.at( 2 ).id().isNull() );
    QVERIFY( !ret.first.at( 2 ).title().isNull() );
    QVERIFY( !ret.second.at( 0 ).id().isNull() );
    QVERIFY( !ret.second.at( 0 ).title().isNull() );
    QVERIFY( !ret.second.at( 1 ).id().isNull() );
    QVERIFY( !ret.second.at( 1 ).title().isNull() );
    QVERIFY( !ret.second.at( 2 ).id().isNull() );
    QVERIFY( !ret.second.at( 2 ).title().isNull() );
}

void PlaylistTest::testDynamicChainXSPF()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "pink floyd^-1" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "the who" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "queen" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "led zeppelin^2" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "-the beatles" ) ) ); //exclude
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistType ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMinHotttnesss, .7 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ArtistMaxFamiliarity, .3 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::MinLoudness, -10 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Mode, 1 ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::ChainXSPF, true ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Format, QLatin1String( "xspf" ) ) );
    Echonest::SongInformation info( Echonest::SongInformation::Hotttnesss | Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistFamiliarity | Echonest::SongInformation::Tracks );
    info.setIdSpaces( QStringList() << QLatin1String( "musicbrainz" ) << QLatin1String( "7digital" ) << QLatin1String( "playme" ) );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::SongInformation, QVariant::fromValue( info ) )  );
    p.append( DynamicPlaylist::PlaylistParamData( DynamicPlaylist::Limit, true ) );

    DynamicPlaylist playlist;
    QNetworkReply* reply = playlist.create( p );

    qDebug() << reply->url().toString();
//     QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/playlist/dynamic?api_key=JGJCRKWLXLBZIFAZB&artist=pink+floyd^-1&artist=the+who&artist=queen&artist=led+zeppelin^2&artist=-the+beatles&type=artist&artist_min_hotttnesss=0.7&artist_max_familiarity=0.3&min_loudness=-10&mode=1&chain_xspf=true&format=xspf&bucket=audio_summary&bucket=song_hotttnesss&bucket=artist_hotttnesss&bucket=artist_familiarity" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    QByteArray xspf = Echonest::DynamicPlaylist::parseXSPFPlaylist( reply );

    //     qDebug() << "xspf:" << xspf;    // verify it's valid
    QDomDocument doc;
    QVERIFY( doc.setContent( xspf ) );
    QVERIFY( !xspf.isEmpty() );

}


QTEST_MAIN( PlaylistTest )

#include "PlaylistTest.moc"

