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

#include "Track.h"

#include "Track_p.h"

Echonest::Track::Track()
  :  d( new TrackData )
{

}


Echonest::Track::Track( const QString& title, const QString& artist, const QString& id, const QString& md5, const QString& release, 
                        const QString& sampleMD5, int analysisChannels, qreal analysisSampleRate, const QString& analyzerVersion, 
                        int bitrate, qreal duration, qreal endOfFadeIn, int key, qreal keyConfidence, qreal loudness, int mode,
                        qreal modeConfidence, int numSamples, int samplerate, qreal startOfFadeOut, qreal tempo, qreal tempoConfidence, const QString& analysisStatus )
    : d( new TrackData )
{
    d->title = title;
    d->artist = artist;
    d->id = id;
    d->md5 = md5;
    d->release = release;
    d->sample_md5 = sampleMD5;
    d->analysis_channels = analysisChannels;
    d->analysis_sample_rate = analysisSampleRate;
    d->analyzer_version = analyzerVersion;
    d->bitrate = bitrate;
    d->duration = duration;
    d->end_of_fade_in = endOfFadeIn;
    d->key = key;
    d->key_confidence = keyConfidence;
    d->loudness = loudness;
    d->mode = mode;
    d->mode_confidence = modeConfidence;
    d->num_samples = numSamples;
    d->samplerate = samplerate;
    d->start_of_fade_out = startOfFadeOut;
    d->tempo = tempo;
    d->tempo_confidence = tempoConfidence;
    d->status = analysisStatus;
}

Echonest::Track::Track(const Echonest::Track& other)
    : d( other.d )
{ }

Echonest::Track::~Track()
{
}


Echonest::Track& Echonest::Track::operator=(const Echonest::Track& track)
{
    d = track.d;
}


QString Echonest::Track::artist() const
{
  return d->artist;
}

QString Echonest::Track::title() const
{
  return d->title;
}

QString Echonest::Track::id() const
{
    return d->id;
}

QString Echonest::Track::md5() const
{
    return d->md5;
}

QString Echonest::Track::release() const
{
    return d->release;
}

QString Echonest::Track::sampleMD5() const
{
    return d->sample_md5;
}


int Echonest::Track::analysisChannels() const
{
    return d->analysis_channels;
}

qreal Echonest::Track::analysisSampleRate() const
{
    return d->analysis_sample_rate;
}

QString Echonest::Track::analyzerVersion() const
{
    return d->analyzer_version;
}

int Echonest::Track::bitrate() const
{
    return d->bitrate;
}

qreal Echonest::Track::duration() const
{
    return d->duration;
}

qreal Echonest::Track::endOfFadeIn() const
{
    return d->end_of_fade_in;
}

int Echonest::Track::key() const
{
    return d->key;
}

qreal Echonest::Track::keyConfidence() const
{
    return d->key_confidence;
}

qreal Echonest::Track::loudness() const
{
    return d->loudness;
}

int Echonest::Track::mode() const
{
    return d->mode;
}

qreal Echonest::Track::modeConfidence() const
{
    return d->mode_confidence;
}

int Echonest::Track::numSamples() const
{
    return d->num_samples;
}

int Echonest::Track::samplerate() const
{
    return d->samplerate;
}

qreal Echonest::Track::startOfFadeOut() const
{
    return d->start_of_fade_out;
}

qreal Echonest::Track::tempo() const
{
    return d->tempo;
}

qreal Echonest::Track::tempoConfidence() const
{
    return d->tempo_confidence;
}

Echonest::Track::AnalysisStatus Echonest::Track::status() const
{
    return statusToEnum( d->status );
}

Echonest::Track::AnalysisStatus Echonest::Track::statusToEnum(const QString& status) const
{
    if( status == QLatin1String("unknown") ) {
        return Echonest::Track::Unknown;
    } else if( status == QLatin1String("pending") ) {
        return Echonest::Track::Pending;
    } else if( status == QLatin1String("complete") ) {
        return Echonest::Track::Complete;
    } else if( status == QLatin1String("error" )) {
        return Echonest::Track::Error;
    }
}

QString Echonest::Track::statusToString(Echonest::Track::AnalysisStatus status) const
{
    switch( status )
    {
    case Echonest::Track::Unknown:
        return QLatin1String( "unknown" );
    case Echonest::Track::Pending:
        return QLatin1String( "pending" );
    case Echonest::Track::Complete:
        return QLatin1String( "complete" );
    case Echonest::Track::Error:
        return QLatin1String( "error" );
    }
            
}


QDebug Echonest::operator<<(QDebug d, const Echonest::Track& track)
{
    d << QString::fromLatin1( "Track(%1, %2, %3" ).arg( track.title() ).arg( track.artist() ).arg( track.release() );
    return d.maybeSpace();
}

