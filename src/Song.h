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
#include "Track.h"

#include <QSharedData>
#include <QHash>
#include <QVariant>
#include <QDebug>
#include <QVector>
#include "Config.h"

class QNetworkReply;

namespace Echonest{

  
/**
 * This encapsulates an Echo Nest song---use it if you wish to get information about a song,
 *   search for a song, etc.
 */
class ECHONEST_EXPORT Song
{
  
public:
  enum SongInformationFlag {
      AudioSummary = 0x0,
      Tracks = 0x1,
      Hotttnesss = 0x2,
      ArtistHotttnesss = 0x4,
      ArtistFamiliarity = 0x8,
      ArtistLocation = 0x16
  };
  Q_DECLARE_FLAGS( SongInformation, SongInformationFlag )

  enum SearchParam {
      Title,
      Artist,
      Combined,
      Description,
      ArtistId,
      Results,
      MaxTempo,
      MinTempo,
      MaxDanceability,
      MinDanceability,
      MaxComplexity,
      MinComplexity,
      MaxDuration,
      MinDuration,
      MaxLoudness,
      MinLoudness,
      MaxFamiliarity,
      MinFamiliarity,
      MaxHotttnesss,
      MinHotttnesss,
      MaxLongitude,
      MinLongitude,
      Mode,
      Key,
      Sort
  };
  typedef QPair< Echonest::Song::SearchParam, QVariant > SearchParamData;
  typedef QVector< SearchParamData > SearchParams;
  
  Song();
  Song( const QString& id, const QString& title, const QString& artistId, const QString& artistName );
  
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
   * To parse the resulting data, call the Song::parseReply() function.
   * 
   */
  QNetworkReply* fetchInformation( SongInformation parts ) const;
  
  /**
   * Search for a song from The Echo Nest with the given search parameters. See 
   *  http://developer.echonest.com/docs/v4/song.html#search for a description of the
   *  parameters and data types.
   * 
   * The result will contain the requested information from the SongInformation flags, and
   *  can be extracted in the parseSearch() function.
   * 
   */
  static QNetworkReply* search( const SearchParams& params, SongInformation parts );
  
  /**
   * Parse the result of the fetchInformation() call.
   * For each requested SongInformationFlag in the original request, a corresponding
   *  key/value pair will be populated. The value depends on the type of request:
   * 
   *   AudioSummary      <--> AudioSummary object
   *   Tracks            <--> QVector< Track >
   *   Hotttnesss        <--> qreal
   *   ArtistHotttnesss  <--> qreal
   *   ArtistFamiliarity <--> qreal
   *   ArtistLocation    <--> ArtistLocation object
   */
  static QHash< SongInformationFlag, QVariant > parseInformation( QNetworkReply* reply ) throw( ParseError );
  
  /**
   * Parse the result of the search() call.
   */
  static QVector<Song> parseSearch( QNetworkReply* reply ) throw( ParseError );
  
  /**
   * Identify a song from a given Echo Nest fingerprint hash code
   * 
   * NOTE this is currently not supported, as the Echo Nest hash code
   *      generator is not currently open source, so I don't care much 
   *      for it.
   *
   * static QNetworkReply* identify(  ) const;
   */
  
  QString toString() const;
  
private:
    static QByteArray searchParamToString( SearchParam param );
    static void addQueryInformation( QUrl& url, SongInformation parts );
    
  QSharedDataPointer<SongData> d;
};


QDebug operator<<(QDebug d, const Song &song);

Q_DECLARE_OPERATORS_FOR_FLAGS(Song::SongInformation)

} // namespace
#endif
