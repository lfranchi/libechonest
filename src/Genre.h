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


#ifndef ECHONEST_GENRE_P_H
#define ECHONEST_GENRE_P_H

#include "Artist.h"

#include <QString>

class QNetworkReply;
class GenreData;
namespace Echonest{

    class Genre;
    typedef QVector< Genre > Genres;

    class ECHONEST_EXPORT Genre {

    public:
        Genre();

        Genre( const Genre& other );
        Genre& operator=( const Genre& genre );
        virtual ~Genre();

        Genre( const QString& name );

        void init();

        QString name() const;
        void setName( const QString& name );

        Artists artists() const;
        void setArtists( const Artists& artists );

        QUrl wikipediaUrl() const;
        void setWikipediaUrl( const QUrl& url );

        QString description() const;
        void setDescription( const QString& description );

        QNetworkReply* fetchArtists( ArtistInformation information = ArtistInformation(), int numResults = 0, bool limit = false );
        QNetworkReply* fetchSimilar( GenreInformation information = GenreInformation(), int numResults = 0, int start = -1 );
        QNetworkReply* fetchProfile( GenreInformation information = GenreInformation() );

        static QNetworkReply* fetchList( GenreInformation information = GenreInformation(), int numResults = 0 );
        static QNetworkReply* fetchSearch( const QString& name, GenreInformation information = GenreInformation(), int numResults = 0, int start = -1 );

        Artists parseArtists( QNetworkReply* ) throw( ParseError );
        Genres parseSimilar( QNetworkReply* ) throw( ParseError );
        void parseProfile( QNetworkReply* ) throw( ParseError );

        static Genres parseList( QNetworkReply* ) throw( ParseError );
        static Genres parseSearch( QNetworkReply* ) throw( ParseError );
    private:
        static QUrl setupStaticQuery( const QByteArray& methodName, int numResults = 0, int start = -1 );
        QUrl setupQuery( const QByteArray& methodName, int numResults = 0, int start = -1 ) const;

        static void addQueryInformation( QUrl& url, GenreInformation information );

        QSharedDataPointer<GenreData> d;

    };

    ECHONEST_EXPORT QDebug operator<<(QDebug d, const Echonest::Genre& genre);

} // namespace

Q_DECLARE_METATYPE( Echonest::Genre )

#endif