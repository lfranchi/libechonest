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

#ifndef ECHONEST_TYPES_P_H
#define ECHONEST_TYPES_P_H

#include <QSharedData>
#include <QString>

class SongData : public QSharedData
{
public:
    SongData() {}
    SongData( const QString& id, const QString& title, const QString& artistName, const QString& artistId )
        : id( id ), title( title ), artistName( artistName ), artistId( artistId ) {}
    
    SongData(const SongData& other)
    {
        id = other.id;
        title = other.title;
        artistName = other.artistName;
        artistId = other.artistId;
    }
    
    ~SongData() {}
    
    QString id;
    QString title;
    QString artistName;
    QString artistId;
    
};

class ArtistData : public QSharedData
{
public:
    ArtistData() {}
    ArtistData( const QString& id, const QString& name ) : id( id ), name( name ) {}
    ArtistData(const ArtistData& other)
    {
        id = other.id;
        name = other.name;
    }
    
    QString id;
    QString name;
};

class TrackData : public QSharedData
{
public:
    // no empty constructor, Tracks can only be created by uploading or getting from MD5
//     TrackData;
    TrackData(const TrackData& other)
    {
        
        analysis_channels = other.analysis_channels;
        analysis_sample_rate = other.analysis_sample_rate;
        analyzer_version = other.analyzer_version;
        artist = other.artist;
//         bars      
//         beats      
        bitrate = other.bitrate;
        duration = other.duration; 
        end_of_fade_in = other.end_of_fade_in;
        id = other.id;
        key = other.key;
        key_confidence = other.key_confidence;
        loudness = other.loudness;
        md5 = other.md5;
//         meta    
        mode = other.mode;
        mode_confidence = other.mode_confidence;
        num_samples = other.num_samples;
        release = other.release;
        sample_md5 = other.sample_md5;
        samplerate = other.samplerate;
        // sections           
        // segments       
        start_of_fade_out = other.start_of_fade_out;
        status = other.status;
        // tatums               
        tempo = other.tempo;
        tempo_confidence = other.tempo_confidence;
        title = other.title;
        
    }
    
    int analysis_channels; //       an int
    qreal analysis_sample_rate; //    a float
    QString analyzer_version; //        ex. '3.01a'
    QString artist; //                  ex. 'The Sea and Cake' or None
    // bars                    a list of dicts
    // beats                   a list of dicts
    int bitrate; //                 an int
    qreal duration; //                a float
    qreal end_of_fade_in; //          a float
    QString id;                     // ex. 'TRTOBXJ1296BCDA33B'
    int key; //                     an int
    qreal key_confidence; //          a float
    qreal loudness; //                a float
    QString md5; //                     ex. '17162ff555969cfed222e127837acd1a'
    // meta                    a dict of analyzer data
    int mode; //                    an int (0 or 1)
    qreal mode_confidence; //         a float
    int num_samples; //             an int
    QString release; //                 the album name, or None
    QString sample_md5; //              '4bf222fb6af22ba0226734bb978bac14'
    int samplerate; //              an int
    // sections                a list of dicts
    // segments                a list of dicts
    qreal start_of_fade_out; //       a float
    int status; //                  ex. 'complete' // enum
    // tatums                  a list of dicts
    qreal tempo; //                   a flat
    qreal tempo_confidence; //        a float
    QString title; //                   ex. 'Interiors' or None
    
};

#endif
