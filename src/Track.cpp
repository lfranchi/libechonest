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

#include "Types_p.h"

Echonest::Track::Track( const QByteArray& xmlData )
  : d( 0 )
{
  // parse with QXmlStreamReader
  // d = new TrackData( ... )
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
