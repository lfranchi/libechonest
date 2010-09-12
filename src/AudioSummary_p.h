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

#include "Util.h"

#include <QSharedData>
#include <QString>
#include <QUrl>
#include <QVector>

class AudioSummaryData : public QSharedData
{
public:
    AudioSummaryData() {}
    AudioSummaryData(const AudioSummaryData& other)
    {
        sessionId = other.sessionId;
        currentSong = other.currentSong;
    }
    
    // basic data that always exists in an Audio Summary object
    int key;
    qreal tempo;
    int mode;
    int time_signature;
    qreal duration;
    qreal loudness;
    
    QUrl analysis_url; // used to fetch the following pieces of data
    
    // meta section
    qreal analysis_time;
    QString analyzer_version;
    QString detailed_status;
    int status;
    qreal timestamp;
    
    // track section
    qreal analysis_sample_rate;
    qreal duration;
    qreal end_of_fade_in;
    int key;
    qreal key_confidence;
    qreal loudness;
    int mode;
    qreal mode_confidence;
    qint64 num_samples;
    QString sample_md5;
    qreal start_of_fade_out;
    qreal tempo;
    qreal tempo_confidence;
    int time_signature;
    qreal time_signature_confidence;
    
    QVector< Echonest::Bar > bars;
    QVector< Echonest::Beat > beats;
    QVector< Echonest::Section > sections;
    QVector< Echonest::Tatum > tatums;
    
    QVector< Echonest::Segment > segments;
    
};

