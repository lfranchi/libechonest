/****************************************************************************************
 * Copyright (c) 2014 Leo Franchi <lfranchi@kde.org>                                    *
 * Copyright (c) 2014 Stefan Derkits <stefan@derkits.at>                                *
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

#include "GenreTest.h"

#include "Genre.h"
#include "Artist.h"
#include "TypeInformation.h"
#include "Config.h"

#include <QNetworkReply>
#include <QDebug>

using namespace Echonest;

void GenreTest::initTestCase()
{
    Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}

void GenreTest::testArtistsUrl()
{
    Genre g;
    g.setName( QLatin1String( "indie folk" ) );

    QNetworkReply* reply = g.fetchArtists();

    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/genre/artists?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=indie+folk&limit=false" ) );

    g.setName( QLatin1String( "funk" ) );

    reply = g.fetchArtists();

    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/genre/artists?api_key=JGJCRKWLXLBZIFAZB&format=xml&name=funk&limit=false" ) );

}

void GenreTest::testArtists()
{
    Genre g;
    g.setName( QLatin1String( "bubblegum pop" ) );

    QNetworkReply* reply = g.fetchArtists( ArtistInformation( ArtistInformation::Genre ) );
    QEventLoop loop;
    qDebug() << reply->url().toString();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    Artists artists = Genre::parseArtists( reply );
    qDebug() << artists;

    QVERIFY( artists.size() > 0 );
    bool genreOK = true;
    foreach(const Echonest::Artist& a, artists)
    {
        bool contains = false;
        foreach(const Echonest::Genre& other, a.genres() ) {
            if (other.name() == g.name())
                contains = true;
        }
        genreOK = genreOK && contains;
    }
    QVERIFY( genreOK );
}

void GenreTest::testListUrl()
{
    QNetworkReply* reply = Genre::fetchList();

    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/genre/list?api_key=JGJCRKWLXLBZIFAZB&format=xml" ) );
}

void GenreTest::testList()
{

    QNetworkReply* reply = Genre::fetchList();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    Genres genres = Genre::parseList( reply );
    qDebug() << genres.size();
    QVERIFY( genres.size() > 0 );

    Genre g;
    g.setName( QLatin1String( "indie rock" ) );

    bool contains = false;
    foreach( const Genre& other, genres )
        if (other.name() == g.name() )
            contains = true;

    QVERIFY( contains );
}

QTEST_MAIN(GenreTest)

#include "GenreTest.moc"
