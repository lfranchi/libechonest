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

#ifndef LIBECHONEST_TRACK_P_H
#define LIBECHONEST_TRACK_P_H

#include <QSharedData>

namespace Echonest
{
  

class TrackData : QSharedData
{
public:
  TrackData() {}
  ~TrackData() {}
  TrackData( const TrackData& other ) : QSharedData( other ) {}
  
  QString artistName;
  QString title;
  QString analysisURL;
  QString trackId;
  QString previewUrl;
  QString audioURL;
  QString audioMD5;
  QString albumName;
  /** TODO analyisStatus */
  qreal tempo;
  qreal loudness;
  qreal duration;
  int timeSignature;
  int key;
  int mode;
  int samplerate;
  int bitrate;
};
  
}

#endif
