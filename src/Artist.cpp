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

#include "Artist.h"
#include "Artist_p.h"

Echonest::Artist::Artist()
    : d( new ArtistData )
{
}

Echonest::Artist::Artist( const QString& id, const QString& name )
    : d( new ArtistData )
{
    d->id = id;
    d->name = name;
}

Echonest::Artist::Artist(const Echonest::Artist& other)
    : d( other.d )
{}

Echonest::Artist& Echonest::Artist::operator=(const Echonest::Artist& artist)
{
    d = artist.d;
}


QString Echonest::Artist::id() const
{
    return d->id;
}

QString Echonest::Artist::name() const
{
    return d->name;
}

void Echonest::Artist::setId(const QString& id)
{
    d->id = id;
}

void Echonest::Artist::setName(const QString& name)
{
    d->name = name;
}

QNetworkReply* Echonest::Artist::fetchAudio() const
{

}

QNetworkReply* Echonest::Artist::fetchBiographies() const
{

}

QNetworkReply* Echonest::Artist::fetchBlogs() const
{

}

QNetworkReply* Echonest::Artist::fetchFamiliarity() const
{

}

QNetworkReply* Echonest::Artist::fetchHotttnesss() const
{

}

QNetworkReply* Echonest::Artist::fetchImages() const
{

}

QNetworkReply* Echonest::Artist::fetchNews() const
{

}

QNetworkReply* Echonest::Artist::fetchProfile() const
{

}

QNetworkReply* Echonest::Artist::fetchSimilar() const
{

}

QNetworkReply* Echonest::Artist::fetchSongs() const
{

}

QNetworkReply* Echonest::Artist::fetchTerms() const
{

}

QNetworkReply* Echonest::Artist::fetchUrls() const
{

}

QNetworkReply* Echonest::Artist::fetchVideo() const
{

}

QDebug Echonest::operator<<(QDebug d, const Echonest::Artist& artist)
{
    d << QString::fromLatin1( "Artist(%1, %2)" ).arg( artist.name() ).arg( artist.id() );
}

