/****************************************************************************************
 * Copyright (c) 2010-2012 Leo Franchi <lfranchi@kde.org>                               *
 * Copyright (c) 2011 Jeff Mitchell <mitchell@kde.org>                                  *
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

#ifndef ECHONEST_TRACK_TEST_H
#define ECHONEST_TRACK_TEST_H

#include <QtTest/QtTest>
#include <QNetworkAccessManager>
#include <QThread>

#include "Config.h"
#include "Track.h"

static QThread* s_mainThread;

class TrackTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    
    void testAnalyzeFromMD5();
    void testAnalyzerFromId();
    void testProfileFromMD5();
    void testProfileFromId();

    void testThreads();
    
private:
    void testUploadLocalFile(); // slow and uploads an mp3, only enable on demand
    void verifyTrack1( const Echonest::Track& track );
    void verifyTrack2( const Echonest::Track& track );
};

class TrackTestThreadObject : public QObject
{
    Q_OBJECT

public:
    TrackTestThreadObject()
    {
    }

    virtual ~TrackTestThreadObject()
    {
    }

public slots:
    void go()
    {
        Echonest::Config::instance()->setNetworkAccessManager( new QNetworkAccessManager() );

        QByteArray id = "TROICNF12B048DE990";
        QNetworkReply* reply = Echonest::Track::analyzeTrackId( id, true );
        QEventLoop loop;
        loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
        loop.exec();

        QVERIFY( reply->error() == QNetworkReply::NoError );
        qDebug() << "main thread is " << s_mainThread << " and current thread is " << QThread::currentThread();
        QVERIFY( QThread::currentThread() != s_mainThread );
        QThread::currentThread()->quit();
    }

};


#endif
