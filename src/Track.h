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
#include <QDebug>
#include <QSharedData>

class TrackData;

namespace Echonest 
{
  
/**
 * Upload-based Echo Nest Track API. If you want to search The Echo Nest for songs, use the Song API. 
 *  If you want to upload your own files and retrieve the acoustic information about them, use this Track
 *   class. You can also fetch acoustic information from a track if you have the Track ID or MD5 of the file.
 * 
 * A Track encapsulates the audio analysis from The Echo Nest
 * 
 */
class ECHONEST_EXPORT Track
{
public:
    
  enum AnalysisStatus {
      Unknown = 0,
      Pending = 1,
      Complete = 2,
      Error = 4
  };
   
  Track();
  Track( const QString& title, const QString& artist, const QString& id, const QString& md5,const QString& release, const QString& sampleMD5,
         int analysisChannels, qreal analysisSampleRate, const QString& analyzerVersion, int bitrate, qreal duration, qreal endOfFadeIn, int key,
         qreal keyConfidence, qreal loudness, int mode, qreal modeConfidence, int numSamples, int samplerate, qreal startOfFadeOut, qreal tempo,
         qreal tempoConfidence, const QString&  status );
  Track( const Track& other );
  Track& operator=( const Track& track );
  ~Track();
  
  QString artist() const;
  QString title() const;
  
  QString id() const;
  QString md5() const;
  QString release() const; // in EN lingo, means albumn ame
  QString sampleMD5() const;
  
  // TODO bars, beats, meta, sections, segments, tatums (the hard stuff! :)
  
  int analysisChannels() const;
  qreal analysisSampleRate() const;
  QString analyzerVersion() const;
  
  int bitrate() const;
  qreal duration() const;
  qreal endOfFadeIn() const;
  int key() const;
  qreal keyConfidence() const;
  qreal loudness() const;
  int mode() const;
  qreal modeConfidence() const;
  int numSamples() const;
  int samplerate() const;
  qreal startOfFadeOut() const;
  qreal tempo() const;
  qreal tempoConfidence() const;
  
  AnalysisStatus status() const;  
  
private:
    AnalysisStatus statusToEnum( const QString& status ) const;
    QString statusToString( AnalysisStatus status ) const;
    
    QSharedDataPointer<TrackData> d;
};

QDebug operator<<(QDebug d, const Echonest::Track& track);


} // namespace

#endif
