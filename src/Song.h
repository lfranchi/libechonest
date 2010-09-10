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


#ifndef ECHONEST_SONG_H
#define ECHONEST_SONG_H

#include "echonest_export.h"
#include "Types_p.h"

#include <QSharedData>

class QNetworkReply;

namespace Echonest{
  
/**
 * This encapsulates an Echo Nest song---use it if you wish to get information about a song,
 *   search for a song, etc.
 */
class ECHONEST_EXPORT Song
{
  
public:
  Song();
  explicit Song( const QByteArray& xmlData );
  
  /**
   * The following pieces of data are present in all Song objects, and do not require
   *   on-demand fetching.
   */
  QString id() const;
  void setId( const QString& id );
  
  QString title() const;
  void setTitle( const QString& title );
  
  QString artistName() const;
  void setArtistName( const QString& artistName );
  
  QString artistId() const;
  void setArtistId( const QString& artistId );
  /** 
   * The following require fetching from The Echo Nest, so return a QNetworkReply*
   *  that is ready for parsing when the finished() signal is emitted.
   * 
   */
  /// TODO Audio Summary
  QNetworkReply* fetchTracks() const;
  QNetworkReply* fetchSongHotttnesss() const;
  QNetworkReply* fetchArtistHotttnesss() const;
  QNetworkReply* fetchArtistFamiliarity() const;
  QNetworkReply* fetchArtistLocation() const;
  
  
private:
  QSharedDataPointer<SongData> d;
};

} // namespace
#endif
