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


#ifndef ECHONEST_TRACK_H
#define ECHONEST_TRACK_H

#include "echonest_export.h"

#include <QObject>
#include <QString>

namespace Echonest 
{

class TrackDataPrivate;
  
/**
 * Upload-based Echo Nest Track API. If you want to search The Echo Nest for songs, use the Song API. 
 *  If you want to upload your own files and retrieve the acoustic information about them, use this Track
 *   class.
 * 
 * A Track encapsulates the audio analysis from The Echo Nest
 * 
 */
class ECHONEST_EXPORT Track : public QObject
{
  Q_OBJECT
  
public:
  explicit Track( const QByteArray& xmlData, QObject* parent = 0 );
  
  //TODO analysis
  QString artistName() const;
  QString title() const;
  QString analysisURL() const;
  
  QString id() const;
  QString audioMD5() const;
  QString audioURL() const;
  QString previewURL() const;
  QString albumName() const; // in EN lingo, 'release'
  
  qreal duration() const;
  qreal loudness() const;
  qreal tempo() const;
  
  int bitrate() const;
  int samplerate() const;
  int key() const;
  int mode() const;
  int timeSignature() const;
  int analyzerVersion() const;
  int channels() const;
  
  
private:
  TrackDataPrivate* const d;
};
  
} // namespace

#endif
