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


#ifndef ECHONEST_ARTIST_H
#define ECHONEST_ARTIST_H

#include "echonest_export.h"

#include <QDebug>
#include <QSharedData>

class QNetworkReply;
class ArtistData;
namespace Echonest{
    
    /**
     * This encapsulates an Echo Nest artist---it always holds the basic info of artist id and
     *  artist name, and can be queried for more data.
     */
    class ECHONEST_EXPORT Artist
    {
        
    public:
        Artist();
        Artist( const QString& id, const QString& name );
        Artist( const Artist& other );
        Artist& operator=( const Artist& artist );
        
        QString id() const;
        void setId( const QString& id );
        
        QString name() const;
        void setName( const QString& name );
        
        /**
         * The following require fetching from The Echo Nest, so return a QNetworkReply*
         *  that is ready for parsing when the finished() signal is emitted.
         * 
         */
        QNetworkReply* fetchAudio() const;
        QNetworkReply* fetchBiographies() const;
        QNetworkReply* fetchBlogs() const;
        QNetworkReply* fetchFamiliarity() const;
        QNetworkReply* fetchHotttnesss() const;
        QNetworkReply* fetchImages() const;
        QNetworkReply* fetchNews() const;
        QNetworkReply* fetchProfile() const;
        QNetworkReply* fetchSongs() const;
        QNetworkReply* fetchSimilar() const;
        QNetworkReply* fetchTerms() const;
        QNetworkReply* fetchUrls() const;
        QNetworkReply* fetchVideo() const;
        
        
    private:
        QSharedDataPointer<ArtistData> d;
    };
    
    QDebug operator<<(QDebug d, const Echonest::Artist& artist);
    
    
} // namespace
#endif
