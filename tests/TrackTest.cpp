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
 
#include "TrackTest.h"

#include "Config.h"
#include "Track.h"

#include <QDebug>
#include <QNetworkReply>
#include <QFile>

void TrackTest::initTestCase()
{
    Echonest::Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}


void TrackTest::testUploadLocalFile()
{
    QFile f( QString::fromLatin1( DATA_DIR "/01 - Cellule.mp3" ) );
    
    QVERIFY( f.exists() );
    QVERIFY( f.open( QIODevice::ReadOnly ) );
    
    QByteArray data = f.readAll();
    
    QVERIFY( !data.isEmpty() );
    
    QUrl path( f.fileName() );
    
    QNetworkReply* reply = Echonest::Track::uploadLocalFile( path, data, true );
    
    qDebug() << "Uploading..";
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    qDebug() << "Verifying uploaded.";
    QVERIFY( reply->error() == QNetworkReply::NoError );
    Echonest::Track track = Echonest::Track::parseProfile( reply );
    
    verifyTrack1( track );
}

void TrackTest::testProfileFromMD5()
{
    QByteArray md5 = "2aceceb60f38e24c3e41365bf26fc7db";
    
    QNetworkReply* reply = Echonest::Track::profileFromMD5( md5 );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QVERIFY( reply->error() == QNetworkReply::NoError );
    Echonest::Track track = Echonest::Track::parseProfile( reply );
    
    verifyTrack1( track );
}

void TrackTest::testProfileFromId()
{
    QByteArray id = "TRMEQQH12B048DE985";
    
    QNetworkReply* reply = Echonest::Track::profileFromTrackId( id );
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QVERIFY( reply->error() == QNetworkReply::NoError );
    Echonest::Track track = Echonest::Track::parseProfile( reply );
    
    verifyTrack1( track );
}

void TrackTest::testAnalyzeFromMD5()
{
    QByteArray md5 = "d41baf84c0d507bf7f861b7820844e05";
    
    QNetworkReply* reply = Echonest::Track::analyzeTrackMD5( md5, true );
    
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QEXPECT_FAIL( "", "profileFromMD5 seems to be broken... :(", Abort );
    QVERIFY( reply->error() == QNetworkReply::NoError );
    try {
        Echonest::Track track = Echonest::Track::parseProfile( reply );
        verifyTrack2( track );   
    } catch( const Echonest::ParseError& e ) {
    }
}

void TrackTest::testAnalyzerFromId()
{
    QByteArray id = "TROICNF12B048DE990";
    
    QNetworkReply* reply = Echonest::Track::analyzeTrackId( id, true );
    
    
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    
    QVERIFY( reply->error() == QNetworkReply::NoError );
    Echonest::Track track = Echonest::Track::parseProfile( reply );
    
    verifyTrack2( track );   
}


void TrackTest::verifyTrack1(const Echonest::Track& track)
{
    QVERIFY( track.status() == Echonest::Analysis::Complete );
    // Echo Nest doesn't have track info for this Jamendo track
    QVERIFY( track.artist().isEmpty() );
    QVERIFY( track.release().isEmpty() );
    QVERIFY( track.title().isEmpty() );
    
    QVERIFY( track.analyzerVersion() == QLatin1String( "3.01a" ) );
    QVERIFY( track.id() == "TRMEQQH12B048DE985" );
    QVERIFY( track.bitrate() == 160 );
    QVERIFY( track.audioMD5() == "2ae41a12e469ba388791b82c11338932" );
    qDebug() << "md5:" << track.md5();
    QVERIFY( track.md5() == "2aceceb60f38e24c3e41365bf26fc7db" );
    QVERIFY( track.samplerate() == 44100 );
    
    // AudioSummary
    QVERIFY( track.audioSummary().key() == 1 );
    QVERIFY( track.audioSummary().tempo() == 160.003 );
    QVERIFY( track.audioSummary().mode() == 0 );
    QVERIFY( track.audioSummary().timeSignature() == 4 );
    QVERIFY( track.audioSummary().duration() == 220.86485 );
    QVERIFY( track.audioSummary().loudness() == -11.839 );
    QVERIFY( track.audioSummary().danceability() > 0 );
    QVERIFY( track.audioSummary().energy() > 0 );
}

void TrackTest::verifyTrack2(const Echonest::Track& track)
{
    QVERIFY( track.status() == Echonest::Analysis::Complete );
    // Echo Nest doesn't have track info for this Jamendo track
    QVERIFY( track.artist().isEmpty() );
    QVERIFY( track.release().isEmpty() );
    QVERIFY( track.title().isEmpty() );
    
    QVERIFY( track.analyzerVersion() == QLatin1String( "3.01a" ) );
    QVERIFY( track.id() == "TROICNF12B048DE990" );
    QVERIFY( track.bitrate() == 160 );
    QVERIFY( track.audioMD5() == "360e25b8f205cb5c730b2b73562f5ebd" );
    qDebug() << "md5:" << track.md5();
    QVERIFY( track.md5() == "d41baf84c0d507bf7f861b7820844e05" );
    QVERIFY( track.samplerate() == 44100 );
    
    // AudioSummary
    QVERIFY( track.audioSummary().key() == 1 );
    QVERIFY( track.audioSummary().tempo() == 135.032 );
    QVERIFY( track.audioSummary().mode() == 1 );
    QVERIFY( track.audioSummary().timeSignature() == 4 );
    QVERIFY( track.audioSummary().duration() == 231.65342 );
    QVERIFY( track.audioSummary().loudness() == -13.473 );
}


QTEST_MAIN(TrackTest)
 
#include "TrackTest.moc"
