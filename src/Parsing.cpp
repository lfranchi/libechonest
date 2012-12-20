/****************************************************************************************
 * Copyright (c) 2010-2012 Leo Franchi <lfranchi@kde.org>                               *
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

#include "Parsing_p.h"

#include "Artist.h"
#include "CatalogItem_p.h"
#include "Util.h"

// QJSon
#include <qjson/parser.h>

#include <QtNetwork/QNetworkReply>
#include <QDateTime>
#include <QStringBuilder>

void Echonest::Parser::checkForErrors( QNetworkReply* reply ) throw( Echonest::ParseError )
{
    if( !reply )
        throw ParseError( Echonest::UnknownError );

    // TODO sometimes this returns false when it shouldn't be? what's going on..
//     if( !reply->isFinished() )
//         throw ParseError( Echonest::UnfinishedQuery );
//
    if( reply->error() != QNetworkReply::NoError && reply->error() != QNetworkReply::UnknownContentError ) {    // let UnknownContentError through so we parse it in readStatus with the proper error message
        ParseError err( Echonest::NetworkError );
        err.setNetworkError( reply->error() );

        throw err;
    }
}

void Echonest::Parser::readStatus( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.readNextStartElement() ) {
        // sanity checks
        if( xml.atEnd() || xml.name() !=  QLatin1String( "response" ) )
            throw ParseError( UnknownParseError );

        if( xml.readNextStartElement() ) {
            if( xml.atEnd() || xml.name() != QLatin1String( "status" ) )
                throw ParseError( UnknownParseError );

            xml.readNextStartElement();
            double version = xml.readElementText().toDouble();
            // TODO use version for something?
            Q_UNUSED(version);
            xml.readNextStartElement();
            Echonest::ErrorType code = static_cast< Echonest::ErrorType >( xml.readElementText().toInt() );
            xml.readNextStartElement();
            QString msg = xml.readElementText();
            xml.readNextStartElement();

            if( code != Echonest::NoError ) {
                qDebug() << "Parse Error:" << code << msg;
                throw ParseError( code, msg );
            }

            xml.readNext();
        }

    } else {
        throw ParseError( UnknownParseError );
    }
}

QVector< Echonest::Song > Echonest::Parser::parseSongList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    QVector< Echonest::Song > songs;

    xml.readNext();
    while( !( xml.name() == QLatin1String( "songs" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        // parse a song
        songs.append( parseSong( xml ) );
    }
    return songs;
}

Echonest::Song Echonest::Parser::parseSong( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "song" ) )
        throw ParseError( Echonest::UnknownParseError );

    Echonest::Song song;
    while( !( xml.name() == QLatin1String( "song" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
            song.setId( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "title" ) && xml.isStartElement() )
            song.setTitle( xml.readElementText() );
        else if( xml.name() == QLatin1String( "artist_id" ) && xml.isStartElement() )
            song.setArtistId( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "artist_name" ) && xml.isStartElement() )
            song.setArtistName( xml.readElementText() );
        else if( xml.name() == QLatin1String( "release" ) && xml.isStartElement() )
            song.setRelease( xml.readElementText() );
        else if( xml.name() == QLatin1String( "song_hotttnesss" ) && xml.isStartElement() )
            song.setHotttnesss( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "artist_hotttnesss" ) && xml.isStartElement() )
            song.setArtistHotttnesss( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "artist_familiarity" ) && xml.isStartElement() )
            song.setArtistFamiliarity( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "tracks" ) && xml.isStartElement() ) {
            song.setTracks( parseSongTrackBucket( xml ) );
        } else if( xml.name() == QLatin1String( "artist_location" ) && xml.isStartElement() ) {
            song.setArtistLocation( parseSongArtistLocation( xml ) );
        } else if( xml.name() == QLatin1String( "audio_summary" ) && xml.isStartElement() ) {
            song.setAudioSummary( parseAudioSummary( xml ) );
        } else if( xml.name() == "song_type" && xml.isStartElement() ) {
            song.addSongType( xml.readElementText() );
        }
        xml.readNext();
    }
    xml.readNext(); // skip past the last </song>

    return song;
}


Echonest::ArtistLocation Echonest::Parser::parseSongArtistLocation( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "artist_location" ) ) {
        throw ParseError( Echonest::UnknownParseError );
    }
    /**
     * while( !( xml.name() ==  "location" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
     x ml.readNex*tStartElement();
     if( xml.name() == "location" )
         song.setArtistLocation( xml.readElementText() );
}
xml.readNext();
**/
    Echonest::ArtistLocation location;
    while( !( xml.name() == QLatin1String( "artist_location" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "latitude" ) && xml.isStartElement() ) {
            location.latitude = xml.readElementText().toDouble();
        } else if( xml.name() == QLatin1String( "longitude" ) && xml.isStartElement() ) {
            location.longitude = xml.readElementText().toDouble();
        } else if( xml.name() == QLatin1String( "location" ) && xml.isStartElement() ) {
            location.location = xml.readElementText();
        }
        xml.readNext();
    }

    return location;
}

Echonest::Tracks Echonest::Parser::parseSongTrackBucket( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "tracks" ) ) {
        throw ParseError( Echonest::UnknownParseError );
    }

    Echonest::Tracks tracks;
    while( !( xml.name() == QLatin1String( "tracks" ) && xml.tokenType() == QXmlStreamReader::EndElement ) && ( xml.name() != QLatin1String( "track" ) || !xml.isEndElement() ) ) {
        if( xml.name() == QLatin1String( "track" ) && xml.isStartElement() ) {
            Echonest::Track track = parseTrack( xml );
            tracks.append( track );
        } else
            xml.readNext();
    }

    return tracks;
}


Echonest::Tracks Echonest::Parser::parseCatalogSongTracks( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "tracks" ) ) {
        throw ParseError( Echonest::UnknownParseError );
    }

    Echonest::Tracks tracks;
    while( !( xml.name() == QLatin1String( "tracks" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "track" ) && xml.isStartElement() ) {
            tracks.append( Echonest::Track( xml.readElementText().toLatin1() ) );
        }
        xml.readNext();
    }

    return tracks;
}

Echonest::Track Echonest::Parser::parseTrack( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "track" ) ) {
        throw ParseError( Echonest::UnknownParseError );
    }
    Echonest::Track track;
    while( !( xml.name() == QLatin1String( "track" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
            track.setId( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "title" ) && xml.isStartElement() )
            track.setTitle( xml.readElementText() );
        else if( xml.name() == QLatin1String( "artist" ) && xml.isStartElement() )
            track.setArtist( xml.readElementText() );
        else if( xml.name() == QLatin1String( "status" ) && xml.isStartElement() )
            track.setStatus( Echonest::statusToEnum( xml.readElementText() ) );
        else if( xml.name() == QLatin1String( "analyzer_version" ) && xml.isStartElement() )
            track.setAnalyzerVersion( xml.readElementText() );
        else if( xml.name() == QLatin1String( "release" ) && xml.isStartElement() )
            track.setRelease( xml.readElementText() );
        else if( xml.name() == QLatin1String( "song_id" ) && xml.isStartElement() )
            track.setSong( Echonest::Song( xml.readElementText().toLatin1() ) );
        else if( xml.name() == QLatin1String( "audio_md5" ) && xml.isStartElement() )
            track.setAudioMD5( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "bitrate" ) && xml.isStartElement() )
            track.setBitrate( xml.readElementText().toInt() );
        else if( xml.name() == QLatin1String( "samplerate" ) && xml.isStartElement() )
            track.setSamplerate( xml.readElementText().toInt() );
        else if( xml.name() == QLatin1String( "md5" ) && xml.isStartElement() )
            track.setMD5( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "catalog" ) && xml.isStartElement() )
            track.setCatalog( xml.readElementText() );
        else if( xml.name() == QLatin1String( "foreign_id" ) && xml.isStartElement() )
            track.setForeignId( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "release_image" ) && xml.isStartElement() )
            track.setReleaseImage( QUrl( xml.readElementText(), QUrl::TolerantMode ) );
        else if( xml.name() == QLatin1String( "preview_url" ) && xml.isStartElement() )
            track.setPreviewUrl( QUrl( xml.readElementText(), QUrl::TolerantMode ) );
        else if( xml.name() == QLatin1String( "audio_summary" ) && xml.isStartElement() ) {
            track.setAudioSummary( parseAudioSummary( xml ) );
            continue;
        }
        xml.readNext();
    }
    xml.readNext(); // skip past the last
    return track;
}


Echonest::AudioSummary Echonest::Parser::parseAudioSummary( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "audio_summary" ) ) {
        throw ParseError( Echonest::UnknownParseError );
    }

    Echonest::AudioSummary summary;
    while( !( xml.name() == QLatin1String( "audio_summary" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "key" ) && xml.isStartElement() )
            summary.setKey( xml.readElementText().toInt() );
        else if( xml.name() == QLatin1String( "analysis_url" ) && xml.isStartElement() )
            summary.setAnalysisUrl( QUrl::fromEncoded( xml.readElementText().toUtf8(), QUrl::TolerantMode ) );
        else if( xml.name() == QLatin1String( "tempo" ) && xml.isStartElement() )
            summary.setTempo( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "mode" ) && xml.isStartElement() )
            summary.setMode( xml.readElementText().toInt() );
        else if( xml.name() == QLatin1String( "time_signature" ) && xml.isStartElement() )
            summary.setTimeSignature( xml.readElementText().toInt() );
        else if( xml.name() == QLatin1String( "duration" ) && xml.isStartElement() )
            summary.setDuration( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "loudness" ) && xml.isStartElement() )
            summary.setLoudness( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "danceability" ) && xml.isStartElement() )
            summary.setDanceability( xml.readElementText().toDouble() );
        else if( xml.name() == QLatin1String( "energy" ) && xml.isStartElement() )
            summary.setEnergy( xml.readElementText().toDouble() );

        xml.readNext();
    }

    return summary;
}

// extract confidence, duration, start out of a list of them. same code for bars, beats, sections, tatums
template< class T >
inline QVector< T > extractTripleTuple( const QVariantList& list ) {
    QVector< T > tList;
    tList.reserve( list.size() );
    for( QVariantList::const_iterator iter = list.constBegin(); iter != list.constEnd(); ++iter ) {
        T t;
        QVariantMap tMap = iter->toMap();
        t.confidence = tMap.value( QLatin1String( "confidence" ), -1 ).toReal();
        t.duration = tMap.value( QLatin1String( "duration" ), -1 ).toReal();
        t.start = tMap.value( QLatin1String( "start" ), -1 ).toReal();

        tList.append( t );
    }
//     qDebug() << "Parsed simple list:" << tList.size();
    return tList;
}

void Echonest::Parser::parseDetailedAudioSummary( QNetworkReply* reply, Echonest::AudioSummary& summary ) throw( ParseError )
{
   QJson::Parser parser;
   bool ok;
   QVariant data = parser.parse( reply, &ok );
   if( !ok ) {
       qWarning() << "Failed to parse JSON data!" << parser.errorString();
       throw ParseError( Echonest::UnknownParseError );
    }
    QVariantMap mainMap = data.toMap();
    if( mainMap.contains( QLatin1String( "meta" ) ) ) {
        QVariantMap metaMap = mainMap.value( QLatin1String( "meta" ) ).toMap();
        summary.setAnalysisTime( metaMap.value( QLatin1String( "analysis_time" ), -1 ).toReal() );
        summary.setAnalysisStatus( metaMap.value( QLatin1String( "status_code" ) ).toInt() );
        summary.setDetailedStatus( metaMap.value( QLatin1String( "detailed_status" ) ).toString() );
        summary.setAnalyzerVersion( metaMap.value( QLatin1String( "analyzer_version" ) ).toString() );
        summary.setTimestamp( metaMap.value( QLatin1String( "analysis_time" ), -1 ).toReal() );
    }
    if( mainMap.contains( QLatin1String( "bars" ) ) ) {
        QVariantList barList = mainMap.value( QLatin1String( "bars" ) ).toList();
        summary.setBars( extractTripleTuple<Echonest::Bar>( barList ) );
    }
    if( mainMap.contains( QLatin1String( "beats" ) ) ) {
        QVariantList beatList = mainMap.value( QLatin1String( "beats" ) ).toList();
        summary.setBeats( extractTripleTuple<Echonest::Beat>( beatList ) );
    }
    if( mainMap.contains( QLatin1String( "sections" ) ) ) {
        QVariantList sectionList = mainMap.value( QLatin1String( "sections" ) ).toList();
        summary.setSections( extractTripleTuple<Echonest::Section>( sectionList ) );
    }
    if( mainMap.contains( QLatin1String( "segments" ) ) ) {
        QVariantList segmentList = mainMap.value( QLatin1String( "segments" ) ).toList();
        Echonest::SegmentList segments;
        segments.reserve( segmentList.size() );
        for( QVariantList::const_iterator iter = segmentList.constBegin(); iter != segmentList.constEnd(); ++iter ) {
            Echonest::Segment segment;
            QVariantMap segmentMap = iter->toMap();
            segment.confidence = segmentMap.value( QLatin1String( "confidence" ), -1 ).toReal();
            segment.duration = segmentMap.value( QLatin1String( "duration" ), -1 ).toReal();
            segment.loudness_max = segmentMap.value( QLatin1String( "loudness_max" ), -1 ).toReal();
            segment.loudness_max_time = segmentMap.value( QLatin1String( "loudness_max_time" ), -1 ).toReal();
            segment.loudness_start = segmentMap.value( QLatin1String( "loudness_start" ), -1 ).toReal();
            // pitches
            QVariantList pitchesList = segmentMap.value( QLatin1String( "pitches" ) ).toList();
            QVector< qreal > pitches;
            pitches.reserve( pitchesList.size() );
            for( QVariantList::const_iterator piter = pitchesList.constBegin(); piter != pitchesList.constEnd(); ++piter )
                pitches.append( piter->toReal() );
            segment.pitches = pitches;
            segment.start = segmentMap.value( QLatin1String( "start" ), -1 ).toReal();
            // timbre
            QVariantList timbreList = segmentMap.value( QLatin1String( "timbre" ) ).toList();
            QVector< qreal > timbres;
            timbres.reserve( timbreList.size() );
            for( QVariantList::const_iterator titer = timbreList.constBegin(); titer != timbreList.constEnd(); ++titer )
                timbres.append( titer->toReal() );
            segment.timbre = timbres;
            segments.append( segment );
        }
        summary.setSegments( segments );
    }
    if( mainMap.contains( QLatin1String( "tatums" ) ) ) {
        QVariantList tatumList = mainMap.value( QLatin1String( "tatums" ) ).toList();
        summary.setTatums( extractTripleTuple<Echonest::Tatum>( tatumList ) );
    }
    if( mainMap.contains( QLatin1String( "track" ) ) ) {
        QVariantMap trackMap = mainMap.value( QLatin1String( "track" ) ).toMap();
        summary.setSampleRate( trackMap.value( QLatin1String( "analysis_sample_rate" ), -1 ).toReal() );
        summary.setEndOfFadeIn( trackMap.value( QLatin1String( "end_of_fade_in" ), -1 ).toReal() );
        summary.setKeyConfidence( trackMap.value( QLatin1String( "key_confidence" ), -1 ).toReal() );
        summary.setModeConfidence( trackMap.value( QLatin1String( "mode_confidence" ), -1 ).toReal() );
        summary.setNumSamples( trackMap.value( QLatin1String( "num_samples" ), -1 ).toLongLong() );
        summary.setSampleMD5( trackMap.value( QLatin1String( "sample_md5" ) ).toString() );
        summary.setStartOfFadeOut( trackMap.value( QLatin1String( "start_of_fade_out" ), -1 ).toReal() );
        summary.setTempoConfidence( trackMap.value( QLatin1String( "tempo_confidence" ), -1 ).toReal() );
        summary.setTimeSignatureConfidence( trackMap.value( QLatin1String( "time_signature_confidence" ), -1 ).toReal() );
    }
}


Echonest::Artists Echonest::Parser::parseArtists( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    // we expect to be in an <artists> start element
    if( xml.atEnd() || xml.name() != QLatin1String( "artists" ) || !xml.isStartElement() )
        throw ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();

    Echonest::Artists artists;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "artists" ) || !xml.isEndElement() ) ) {
        if( xml.atEnd() || xml.name() != QLatin1String( "artist" ) || !xml.isStartElement() )
            throw Echonest::ParseError( Echonest::UnknownParseError );
        Echonest::Artist artist;
        while( !xml.atEnd() && ( xml.name() != QLatin1String( "artist" ) || !xml.isEndElement() ) ) {
            parseArtistInfo( xml, artist );
            xml.readNextStartElement();
        }
        artists.append( artist );

        xml.readNext();
    }
    return artists;
}

int Echonest::Parser::parseArtistInfoOrProfile( QXmlStreamReader& xml , Echonest::Artist& artist  ) throw( Echonest::ParseError )
{
    if( xml.name() == QLatin1String( "start" ) ) { // this is an individual info query, so lets read it
        xml.readNextStartElement();
        xml.readNext();

        int results = -1;
        if( xml.name() == QLatin1String( "total" ) ) {
            results = xml.readElementText().toInt();
            xml.readNextStartElement();
        }

        parseArtistInfo( xml, artist );

        return results;
    } else if( xml.name() == QLatin1String( "songs" ) ) {
        parseArtistSong( xml, artist );
    } else if( xml.name() == QLatin1String( "urls" ) ) { // urls also has no start/total
        parseUrls( xml, artist );
    } else { // this is either a profile query, or a familiarity or hotttness query, so save all the data we find
        while( !( xml.name() == QLatin1String( "artist" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
            parseArtistInfo( xml, artist );
            xml.readNextStartElement();
        }
    }

    return 0;
}

void Echonest::Parser::parseArtistInfo( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    // parse each sort of artist information
    if( xml.name() == QLatin1String( "audio" ) ) {
        parseAudio( xml, artist );
    } else if( xml.name() == QLatin1String( "biographies" ) ) {
        parseBiographies( xml, artist );
    } else if( xml.name() == QLatin1String( "familiarity" ) ) {
        artist.setFamiliarity( xml.readElementText().toDouble() );
    }  else if( xml.name() == QLatin1String( "hotttnesss" ) ) {
        artist.setHotttnesss( xml.readElementText().toDouble() );
    }  else if( xml.name() == QLatin1String( "images" ) ) {
        parseImages( xml, artist );
    }  else if( xml.name() == QLatin1String( "news" ) && xml.isStartElement() ) {
        parseNewsOrBlogs( xml, artist, true );
    }  else if( xml.name() == QLatin1String( "blogs" ) ) {
        parseNewsOrBlogs( xml, artist, false );
    }  else if( xml.name() == QLatin1String( "reviews" ) ) {
        parseReviews( xml, artist );
    }  else if( xml.name() == QLatin1String( "terms" ) ) {
        parseTerms( xml, artist );
    }  else if( xml.name() == QLatin1String( "urls" ) ) {
        parseTerms( xml, artist );
    }  else if( xml.name() == QLatin1String( "songs" ) ) {
        parseArtistSong( xml, artist );
    }  else if( xml.name() == QLatin1String( "video" ) ) {
        parseVideos( xml, artist );
    }  else if( xml.name() == QLatin1String( "foreign_ids" ) ) {
        parseForeignArtistIds( xml, artist );
    }  else if( xml.name() == QLatin1String( "name" ) ) {
        artist.setName( xml.readElementText() );
    }  else if( xml.name() == QLatin1String( "id" ) ) {
        artist.setId( xml.readElementText().toLatin1() );
    }
}


// parse each type of artist attribute

void Echonest::Parser::parseAudio( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "audio" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();
    Echonest::AudioList audioList;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "audio" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::AudioFile audio;
        do {
            xml.readNext();
            if( xml.name() == QLatin1String( "title" ) )
                audio.setTitle( xml.readElementText() );
            else if( xml.name() == QLatin1String( "url" ) )
                audio.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "artist" ) )
                audio.setArtist(  xml.readElementText() );
            else if( xml.name() == QLatin1String( "date" ) )
                audio.setDate( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == QLatin1String( "length" ) )
                audio.setLength( xml.readElementText().toDouble() );
            else if( xml.name() == QLatin1String( "link" ) )
                audio.setLink( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "release" ) )
                audio.setRelease( xml.readElementText() );
            else if( xml.name() == QLatin1String( "id" ) )
                audio.setId( xml.readElementText().toLatin1() );

        } while( !xml.atEnd() && ( xml.name() != QLatin1String( "audio" ) || xml.tokenType() != QXmlStreamReader::EndElement ) );
        audioList.append( audio );
        xml.readNext();
    }
    artist.setAudio( audioList );
}

void Echonest::Parser::parseBiographies( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "biographies" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();
    Echonest::BiographyList bios;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "biographies" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::Biography bio;
        do {
            xml.readNext();

            if( xml.name() == QLatin1String( "text" ) )
                bio.setText( xml.readElementText() );
            else if( xml.name() == QLatin1String( "site" ) )
                bio.setSite( xml.readElementText() );
            else if( xml.name() == QLatin1String( "url" ) )
                bio.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "license" ) )
                bio.setLicense( parseLicense( xml) );

        } while( !xml.atEnd() && ( xml.name() != QLatin1String( "biography" ) || xml.tokenType() != QXmlStreamReader::EndElement ) );
        bios.append( bio );
        xml.readNext();
    }
    artist.setBiographies( bios );
}


void Echonest::Parser::parseImages( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "images" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();
    Echonest::ArtistImageList imgs;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "images" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::ArtistImage img;
        do {
            xml.readNext();

            if( xml.name() == QLatin1String( "url" ) )
                img.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "license" ) )
                img.setLicense( parseLicense( xml) );

        } while( !xml.atEnd() && ( xml.name() != QLatin1String( "image" ) || xml.tokenType() != QXmlStreamReader::EndElement ) );
        imgs.append( img );
        xml.readNext();
    }
    artist.setImages( imgs );
}

void Echonest::Parser::parseNewsOrBlogs( QXmlStreamReader& xml, Echonest::Artist& artist, bool news  ) throw( Echonest::ParseError )
{
    if( news && ( xml.atEnd() || xml.name() != QLatin1String( "news" ) || xml.tokenType() != QXmlStreamReader::StartElement ) )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    else if( !news && ( xml.atEnd() || xml.name() != QLatin1String( "blogs" ) || xml.tokenType() != QXmlStreamReader::StartElement ) )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();
    Echonest::NewsList newsList;
    while( !( ( xml.name() == QLatin1String( "news" ) || xml.name() == QLatin1String( "blogs" ) ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        Echonest::NewsArticle news;
        do {
            xml.readNextStartElement();

            if( xml.name() == QLatin1String( "name" ) )
                news.setName( xml.readElementText() );
            else if( xml.name() == QLatin1String( "url" ) )
                news.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "summary" ) )
                news.setSummary(  xml.readElementText() );
            else if( xml.name() == QLatin1String( "date_found" ) )
                news.setDateFound( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == QLatin1String( "id" ) )
                news.setId( xml.readElementText().toLatin1() );
            else if( xml.name() == QLatin1String( "date_posted" ) )
                news.setDatePosted( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
        } while( !( ( xml.name() == QLatin1String( "news" ) || xml.name() == QLatin1String( "blog" ) ) && xml.tokenType() == QXmlStreamReader::EndElement ) );
        newsList.append( news );
        xml.readNext();
    }
    if( news )
        artist.setNews( newsList );
    else
        artist.setBlogs( newsList );
}

void Echonest::Parser::parseReviews( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "reviews" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();
    Echonest::ReviewList reviews;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "reviews" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::Review review;
        do {
            xml.readNextStartElement();

            if( xml.name() == QLatin1String( "url" ) )
                review.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "name" ) )
                review.setName( xml.readElementText() );
            else if( xml.name() == QLatin1String( "summary" ) )
                review.setSummary( xml.readElementText() );
            else if( xml.name() == QLatin1String( "date_found" ) )
                review.setDateFound( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == QLatin1String( "image" ) )
                review.setImageUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "release" ) )
                review.setRelease( xml.readElementText() );
            else if( xml.name() == QLatin1String( "id" ) )
                review.setId( xml.readElementText().toLatin1() );

        } while( !xml.atEnd() && ( xml.name() != QLatin1String( "review" ) || xml.tokenType() != QXmlStreamReader::EndElement ) );
        reviews.append( review );
        xml.readNext();
    }
    artist.setReviews( reviews );
}

void Echonest::Parser::parseArtistSong( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "songs" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    xml.readNextStartElement();
    Echonest::SongList songs;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "songs" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "song" ) && xml.isStartElement() )
        {
            Echonest::Song song;
            while( !xml.atEnd() && ( xml.name() != QLatin1String( "song" ) || !xml.isEndElement() ) ) {
                if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
                    song.setId( xml.readElementText().toLatin1() );
                else if( xml.name() == QLatin1String( "title" ) && xml.isStartElement() )
                    song.setTitle( xml.readElementText() );
                xml.readNextStartElement();
            }
            songs.append( song );
        }
        xml.readNext();
    }
    artist.setSongs( songs );
}

void Echonest::Parser::parseTerms( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "terms" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    artist.setTerms( parseTopTermList( xml ) );
}

Echonest::Artists Echonest::Parser::parseArtistSuggestList( QXmlStreamReader& xml ) throw( ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "artists" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::Artists artists;

    xml.readNextStartElement();
    while( xml.name() != QLatin1String( "artists" ) || !xml.isEndElement() ) {
        QString name;
        QByteArray id;
        while( xml.name() != QLatin1String( "artist" ) || !xml.isEndElement() ) {
            if( xml.name() == QLatin1String( "name" ) && xml.isStartElement() )
                name = xml.readElementText();
            else if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
                id = xml.readElementText().toLatin1();
            xml.readNext();
        }
        artists << Echonest::Artist( id, name );
        xml.readNext();
    }
    return artists;
}


void Echonest::Parser::parseUrls( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "urls" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    xml.readNextStartElement();
//     xml.readNextStartElement();

    while( !xml.atEnd() && ( xml.name() != QLatin1String( "urls" ) || !xml.isEndElement() ) ) {
        if( xml.name() == QLatin1String( "lastfm_url" ) )
            artist.setLastFmUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == QLatin1String( "aolmusic_url" ) )
            artist.setAolMusicUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == QLatin1String( "myspace_url" ) )
            artist.setMyspaceUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == QLatin1String( "amazon_url" ) )
            artist.setAmazonUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == QLatin1String( "itunes_url" ) )
            artist.setItunesUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == QLatin1String( "mb_url" ) )
            artist.setMusicbrainzUrl( QUrl( xml.readElementText() ) );

        xml.readNextStartElement();
    }
    xml.readNextStartElement();
}

void Echonest::Parser::parseVideos( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "video" )|| xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::VideoList videos;
    while( xml.name() == QLatin1String( "video" ) && xml.isStartElement() ) {

        Echonest::Video video;

        while( !xml.atEnd() && ( xml.name() != QLatin1String( "video" ) || !xml.isEndElement() ) ) {
            if( xml.name() == QLatin1String( "title" ) )
                video.setTitle( xml.readElementText() );
            else if( xml.name() == QLatin1String( "url" ) )
                video.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "site" ) )
                video.setSite( xml.readElementText() );
            else if( xml.name() == QLatin1String( "date_found" ) )
                video.setDateFound( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == QLatin1String( "image_url" ) )
                video.setImageUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == QLatin1String( "id" ) )
                video.setId( xml.readElementText().toLatin1() );

            xml.readNextStartElement();
        }
        videos.append( video );

        xml.readNextStartElement();
    }
    artist.setVideos( videos );
}

Echonest::TermList Echonest::Parser::parseTopTermList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "terms" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::TermList terms;
    while( xml.name() == QLatin1String( "terms" ) && xml.isStartElement() ) {
        Echonest::Term term;
//         qDebug() << "Parsing term outer item:" << xml.name() << xml.isStartElement();
        while( !xml.atEnd() && ( xml.name() != QLatin1String( "terms" ) || !xml.isEndElement() ) ) {
            if( xml.name() == QLatin1String( "frequency" ) )
                term.setFrequency( xml.readElementText().toDouble() );
            else if( xml.name() == QLatin1String( "name" ) )
                term.setName( xml.readElementText() );
            else if( xml.name() == QLatin1String( "weight" ) )
                term.setWeight( xml.readElementText().toDouble() );

            xml.readNextStartElement();
        }
        terms.append( term );
//         qDebug() << "Parsing exernal term item:" << xml.name() << xml.isStartElement();

        xml.readNext();
    }
//     qDebug() << " done Parsing terms:" << xml.name() << xml.isStartElement();

    return terms;
}


QVector< QString > Echonest::Parser::parseTermList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "terms" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QVector< QString > terms;
    while( xml.name() != QLatin1String( "response" ) || !xml.isEndElement() ) {
        if( xml.name() == QLatin1String( "name" ) && xml.isStartElement() )
            terms.append( xml.readElementText() );
        xml.readNextStartElement();
    }

    return terms;
}

QVector< QString > Echonest::Parser::parseGenreList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "genres" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QVector< QString > genres;
    while( xml.name() != "response" || !xml.isEndElement() ) {
        if( xml.name() == "name" && xml.isStartElement() )
            genres.append( xml.readElementText() );
        xml.readNextStartElement();
    }

    return genres;
}

void Echonest::Parser::parseForeignArtistIds( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "foreign_ids" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::ForeignIds ids;
    while( xml.name() != QLatin1String( "foreign_ids" ) || !xml.isEndElement() ) {
        xml.readNext();
        xml.readNext(); // get past the enclosing <foreign_id>, or else we'll think it's the internal one.
        Echonest::ForeignId id;
        while( xml.name() != QLatin1String( "foreign_id" ) || !xml.isEndElement() ) {
            if( xml.name() == QLatin1String( "catalog" ) && xml.isStartElement() )
                id.catalog = xml.readElementText();
            else if( xml.name() == QLatin1String( "foreign_id" ) && xml.isStartElement() )
                id.foreign_id = xml.readElementText();

            xml.readNext();
        }
        ids.append( id );
        xml.readNext();
    }
    artist.setForeignIds( ids );
}

Echonest::License Echonest::Parser::parseLicense( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "license" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::License license;
    while( !xml.atEnd() && ( xml.name() != QLatin1String( "license" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        if( xml.name() == QLatin1String( "type" ) )
            license.type = xml.readElementText();
        else if( xml.name() == QLatin1String( "attribution" ) )
            license.attribution = xml.readElementText();
        else if( xml.name() == QLatin1String( "url" ) )
            license.url = QUrl( xml.readElementText() );

        xml.readNext();
    }

    xml.readNextStartElement();
    return license;
}

QByteArray Echonest::Parser::parsePlaylistSessionId( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "session_id" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QByteArray sessionId = xml.readElementText().toLatin1();
    xml.readNext(); //read to next start element
    return sessionId;
}

Echonest::SongList Echonest::Parser::parseDynamicLookahead( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::SongList lookahead;

    // Might not be any
    if ( xml.name() != QLatin1String( "lookahead" ) )
        return lookahead;

    while( !xml.atEnd() && ( xml.name() == QLatin1String( "lookahead" ) && xml.tokenType() == QXmlStreamReader::StartElement ) ) {
        // Read each lookahead track
        Echonest::Song song;
        while( !xml.atEnd() && ( xml.name() != QLatin1String( "lookahead" ) || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
            if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
                song.setId( xml.readElementText().toLatin1() );
            else if( xml.name() == QLatin1String( "title" ) && xml.isStartElement() )
                song.setTitle( xml.readElementText() );
            else if( xml.name() == QLatin1String( "artist_id" ) && xml.isStartElement() )
                song.setArtistId( xml.readElementText().toLatin1() );
            else if( xml.name() == QLatin1String( "artist_name" ) && xml.isStartElement() )
                song.setArtistName( xml.readElementText() );

            xml.readNext();
        }
        lookahead.append(song);

        xml.readNext();
    }

    return lookahead;
}

// Catalogs parseCatalogList( QXmlStreamReader& xml ) throw( ParseError );
Echonest::Catalogs Echonest::Parser::parseCatalogList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    int total = -1;
    while( xml.name() != QLatin1String( "response" ) && ( xml.name() != QLatin1String( "catalogs" ) || !xml.isStartElement() ) ) {
        if( xml.name() == QLatin1String( "total" ) && xml.isStartElement() )
            total = xml.readElementText().toInt();
        xml.readNextStartElement();
    }


    Echonest::Catalogs catalogs;

    if( xml.name() != QLatin1String( "catalogs" ) ) { // none
        return catalogs;
    }

    catalogs.reserve( total );
    // now we're pointing at the first catalog
    while( xml.name() != QLatin1String( "response" ) || !xml.isEndElement() )
        catalogs.append( Echonest::Parser::parseCatalog( xml ) );

    return catalogs;
}

Echonest::Catalog Echonest::Parser::parseCatalog( QXmlStreamReader& xml, bool justOne ) throw( Echonest::ParseError )
{
    QString cName = justOne ? QLatin1String( "catalog" ) : QLatin1String( "catalogs" );
    if( xml.atEnd() || xml.name() != cName || !xml.isStartElement() )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    xml.readNextStartElement();

    Echonest::Catalog catalog;
    while( xml.name() != cName || !xml.isEndElement() ) {
        if( xml.name() == QLatin1String( "total" ) && xml.isStartElement() )
            catalog.setTotal( xml.readElementText().toInt() );
        else if( xml.name() == QLatin1String( "type" ) && xml.isStartElement() )
            catalog.setType( Echonest::literalToCatalogType( xml.readElementText().toLatin1() ) );
        else if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
            catalog.setId( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "name" ) && xml.isStartElement() )
            catalog.setName( xml.readElementText() );
        else if( xml.name() == QLatin1String( "items" ) && xml.isStartElement() ) {
            QList<Echonest::CatalogItem*> items = parseCatalogItems( xml );
            if( items.isEmpty() ) {
                xml.readNextStartElement();
                continue;
            }
            if( items[ 0 ]->type() == Echonest::CatalogTypes::Artist ) {
                saveArtistList( catalog, items );
            } else if( items[ 0 ]->type() == Echonest::CatalogTypes::Song ) {
                saveSongList( catalog, items );
            }
        }
        xml.readNextStartElement();
    }
    xml.readNext();

    return catalog;
}

QList<Echonest::CatalogItem*> Echonest::Parser::parseCatalogItems( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "items" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QList<Echonest::CatalogItem*> items;
    while( xml.name() == QLatin1String( "items" ) && xml.isStartElement() ) {
        // OK, the mixture of the crappy Catalog API and strongly typed c++ makes this ugly. We don't know if this is an artist or song until we reach the artist_id or song_id.
        //  so, we'll keep two copies till the end, where we throw away one. :(
        Echonest::CatalogArtist* artist = new Echonest::CatalogArtist;
        Echonest::CatalogSong* song = new CatalogSong;
        while( xml.name() != QLatin1String( "items" ) || !xml.isEndElement() ) {
            // OK, we have to check for all possible song+artist types :'(
            if( xml.name() == QLatin1String( "rating" ) && xml.isStartElement() ) { /// mixed and artist items
                artist->setRating( xml.readElementText().toInt() );
                song->setRating( artist->rating() );
            } else if( xml.name() == QLatin1String( "request" ) && xml.isStartElement() ) {
                parseCatalogRequestItem( xml, *artist, *song );
            } else if( xml.name() == QLatin1String( "artist_name" ) && xml.isStartElement() ) {
                artist->setName( xml.readElementText() );
                song->setArtistName( artist->name() );
            } else if( xml.name() == QLatin1String( "reviews" ) && xml.isStartElement() ) {
                parseReviews( xml, *artist );
            } else if( xml.name() == QLatin1String( "terms" ) && xml.isStartElement() ) {
                parseTerms( xml, *artist );
                continue;
            } else if( xml.name() == QLatin1String( "biographies" ) && xml.isStartElement() ) {
                parseBiographies( xml, *artist );
            } else if( xml.name() == QLatin1String( "familiarity" ) && xml.isStartElement() ) {
                artist->setFamiliarity( xml.readElementText().toDouble() );
                song->setArtistFamiliarity( artist->familiarity() );
            } else if( xml.name() == QLatin1String( "blogs" ) && xml.isStartElement() ) {
                parseNewsOrBlogs( xml, *artist, false );
            } else if( xml.name() == QLatin1String( "hotttnesss" ) && xml.isStartElement() ) {
                artist->setHotttnesss( xml.readElementText().toDouble() );
                song->setArtistHotttnesss( artist->hotttnesss() );
            } else if( xml.name() == QLatin1String( "video" ) && xml.isStartElement() ) {
                parseVideos( xml, *artist );
            } else if( xml.name() == QLatin1String( "urls" ) && xml.isStartElement() ) {
                parseUrls( xml, *artist );
            } else if( xml.name() == QLatin1String( "news" ) && xml.isStartElement() ) {
                parseNewsOrBlogs( xml, *artist );
            } else if( xml.name() == QLatin1String( "images" ) && xml.isStartElement() ) {
                parseImages( xml, *artist );
            } else if( xml.name() == QLatin1String( "date_added" ) && xml.isStartElement() ) {
                artist->setDateAdded( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
                song->setDateAdded( artist->dateAdded() );
            } else if( xml.name() == QLatin1String( "artist_id" ) && xml.isStartElement() ) {
                artist->setId( xml.readElementText().toLatin1() );
                song->setArtistId( artist->id() );
            } else if( xml.name() == QLatin1String( "audio" ) && xml.isStartElement() ) {
                parseAudio( xml, *artist );
            } else if( xml.name() == QLatin1String( "foreign_id" ) && xml.isStartElement() ) {
                artist->setForeignId( xml.readElementText().toLatin1()  );
                song->setForeignId( artist->foreignId() );
            } else if( xml.name() == QLatin1String( "song_id" ) && xml.isStartElement() ) { /// song-specific entries
                song->setId( xml.readElementText().toLatin1() );
            } else if( xml.name() == QLatin1String( "song_name" ) && xml.isStartElement() ) {
                song->setTitle( xml.readElementText() );
            } else if( xml.name() == QLatin1String( "tracks" ) && xml.isStartElement() ) {
                song->setTracks( parseCatalogSongTracks( xml ) );
            } else if( xml.name() == QLatin1String( "play_count" ) && xml.isStartElement() ) {
               static_cast<Echonest::CatalogSong*>(song)->setPlayCount( xml.readElementText().toInt() );
            } else if( xml.name() == QLatin1String( "artist_hotttnesss" ) && xml.isStartElement() ) {
                song->setArtistHotttnesss( xml.readElementText().toDouble() );
            } else if( xml.name() == QLatin1String( "artist_location" ) && xml.isStartElement() ) {
                // TODO
            } else if( xml.name() == QLatin1String( "song_hotttnesss" ) && xml.isStartElement() ) {
                song->setHotttnesss( xml.readElementText().toDouble() );
            } else if( xml.name() == QLatin1String( "artist_familiarity" ) && xml.isStartElement() ) {
                song->setArtistFamiliarity( xml.readElementText().toDouble() );
            } else if( xml.name() == QLatin1String( "audio_summary" ) && xml.isStartElement() ) {
                song->setAudioSummary( parseAudioSummary( xml ) );
            }
            xml.readNextStartElement();
        }
        if( !song->id().isEmpty() ) { // No song id, so it's an artist.
//             qDebug() << "Adding a song";
            items << song;
            delete artist;
        } else if( !artist->id().isEmpty() ) {
//             qDebug() << "Adding an artist";
            items << artist;
            delete song;
        } else { // dunno what this is really. lets use the song one for now
//             qDebug() << "Adding an EMPTY";
            items << song;
            delete artist;
        }
        xml.readNext();
    }

    return items;
}

void Echonest::Parser::parseCatalogRequestItem( QXmlStreamReader& xml, Echonest::CatalogArtist& artist, Echonest::CatalogSong& song) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "request" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    Echonest::CatalogUpdateEntry request;
    while( xml.name() != QLatin1String( "request" ) || !xml.isEndElement() ) {
        if( xml.name() == QLatin1String( "item_id" ) ) {
            request.setItemId( xml.readElementText().toLatin1() );
        } else if( xml.name() == QLatin1String( "artist_name" ) ) {
            request.setArtistName( xml.readElementText() );
        } else if( xml.name() == QLatin1String( "song_name" ) ) {
            request.setSongName( xml.readElementText() );
        } else if( xml.name() == QLatin1String( "fp_code" ) ) {
            request.setFingerprint( xml.readElementText().toLatin1() );
        } else if( xml.name() == QLatin1String( "song_id" ) ) {
            request.setSongId( xml.readElementText().toLatin1() );
        } else if( xml.name() == QLatin1String( "artist_id" ) ) {
            request.setArtistId( xml.readElementText().toLatin1() );
        } else if( xml.name() == QLatin1String( "release" ) ) {
            request.setRelease( xml.readElementText() );
        } else if( xml.name() == QLatin1String( "genre" ) ) {
            request.setGenre( xml.readElementText() );
        }
        xml.readNext();
    }
    artist.setRequest( request );
    song.setRequest( request );
}

void Echonest::Parser::saveArtistList( Echonest::Catalog& catalog, QList<Echonest::CatalogItem*>& artists)
{
    // will copy artists into the catalog, and delete the origin
    Echonest::CatalogArtists ca;
    foreach( const Echonest::CatalogItem* item, artists ) {
        ca.append( CatalogArtist( *static_cast<const CatalogArtist*>( item ) ) );
    }
    qDeleteAll( artists );
    catalog.setArtists( ca );
}

void Echonest::Parser::saveSongList( Echonest::Catalog& catalog, QList<Echonest::CatalogItem*>& songs)
{
    // will copy songs into the catalog, and delete the origin
    Echonest::CatalogSongs ca;
    foreach( const Echonest::CatalogItem* item, songs ) {
        ca.append( CatalogSong( *static_cast<const CatalogSong*>( item ) ) );
    }
    qDeleteAll( songs );
    catalog.setSongs( ca );
}


Echonest::CatalogStatus Echonest::Parser::parseCatalogStatus( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    Echonest::CatalogStatus status;

    while( xml.name() != QLatin1String( "response" ) || !xml.isEndElement() ) {
        if( xml.name() == QLatin1String( "ticket_status" ) && xml.isStartElement() )
            status.status = Echonest::literalToCatalogStatus( xml.readElementText().toLatin1() );
        else if( xml.name() == QLatin1String( "details" ) && xml.isStartElement() )
            status.details = xml.readElementText();
        else if( xml.name() == QLatin1String( "items_updated" ) && xml.isStartElement() )
            status.items_updated = xml.readElementText().toInt();
        else if( xml.name() == QLatin1String( "update_info" ) && xml.isStartElement() )
            status.items = parseTicketUpdateInfo( xml );
//         else if( xml.name() == "percent_complete" && xml.isStartElement() )
//             status.percent_complete = xml.readElementText().toInt();

        xml.readNext();
    }

    return status;
}

Echonest::CatalogStatusItem Echonest::Parser::parseTicketUpdateInfo( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
//     if( xml.atEnd() || xml.name() != "ticket_status" || xml.tokenType() != QXmlStreamReader::StartElement )
//         throw Echonest::ParseError( Echonest::UnknownParseError );
        // TODO
        return Echonest::CatalogStatusItem();
}

QByteArray Echonest::Parser::parseCatalogTicket( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "ticket" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QByteArray ticket= xml.readElementText().toLatin1();
    return ticket;
}

Echonest::Catalog Echonest::Parser::parseNewCatalog( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QString name;
    QByteArray id;
    Echonest::CatalogTypes::Type type = Echonest::CatalogTypes::Artist;

    qDebug() << "Parsing new catalog...";
    while( xml.name() != QLatin1String( "response" ) || !xml.isEndElement() ) {
        qDebug() << "Parsing at:" << xml.name().toString();
        if( xml.name() == QLatin1String( "name" ) && xml.isStartElement() )
            name = xml.readElementText();
        else if( xml.name() == QLatin1String( "id" ) && xml.isStartElement() )
            id = xml.readElementText().toLatin1();
        else if( xml.name() == QLatin1String( "type" ) && xml.isStartElement() )
            type = Echonest::literalToCatalogType( xml.readElementText().toLatin1() );

        xml.readNextStartElement();
        qDebug() << "Parsing next at:" << xml.name().toString();
    }
    Echonest::Catalog c = Echonest::Catalog( id );
    c.setName( name );
    c.setType( type );

    return c;
}

Echonest::SessionInfo Echonest::Parser::parseSessionInfo( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    Echonest::SessionInfo info;

    while( xml.name() != QLatin1String( "response" ) || !xml.isEndElement() ) {
//         qDebug() << "Parsing part of session info:" << xml.name() << xml.isStartElement();
        // TODO
    /** Sample output:
     http://files.lfranchi.com/echonest_dynamic_info.xml


        if( xml.name() == "terms" && xml.isStartElement() ) {
            info.terms = parseTopTermList( xml );
            continue;
        } else if( xml.name() == "rules" && xml.isStartElement() ) {
            info.rules = parseRulesList( xml );
            continue;
        } else if( xml.name() == "session_id" && xml.isStartElement() )
            info.session_id = xml.readElementText().toLatin1();
        else if( xml.name() == "seeds" && xml.isStartElement() )
            info.seeds.append( Artist( xml.readElementText().toLatin1() ) );
        else if( xml.name() == "banned_artists" && xml.isStartElement() )
            info.banned_artists.append( Artist( xml.readElementText().toLatin1() ) );
        else if( xml.name() == "seed_songs" && xml.isStartElement() )
            info.seed_songs.append( Song( xml.readElementText().toLatin1() ) );
        else if( xml.name() == "seed_catalog" && xml.isStartElement() )
            info.seed_catalogs.append( Catalog( xml.readElementText().toLatin1() ) );
        else if( xml.name() == "playlist_type" && xml.isStartElement() )
            info.playlist_type = xml.readElementText();
        else if( xml.name() == "skipped_songs" && xml.isStartElement() ) {
            info.skipped_songs = parseSessionSongItem( xml, QLatin1String( "skipped_songs" ) );
            continue;
        } else if( xml.name() == "banned_songs" && xml.isStartElement() ) {
            info.banned_songs = parseSessionSongItem( xml, QLatin1String( "banned_songs" ) );
            continue;
        } else if( xml.name() == "rated_songs" && xml.isStartElement() ) {
            info.rated_songs = parseSessionSongItem( xml, QLatin1String( "rated_songs" ) );
            continue;
        } else if( xml.name() == "history" && xml.isStartElement() ) {
            info.history = parseSessionSongItem( xml, QLatin1String( "history" ) );
            continue;
        }*/
        xml.readNext();
    }
    return info;
}


QVector< QString > Echonest::Parser::parseRulesList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != QLatin1String( "rules" ) || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QVector< QString > rules;
    while( xml.name() == QLatin1String( "rules" ) && xml.isStartElement() ) {
//         qDebug() << "Parsing start of rules:" << xml.name() << xml.isStartElement();
        xml.readNextStartElement();
        rules.append( xml.readElementText() );
        xml.readNext();
        xml.readNext();
//         qDebug() << "Parsing end of rules:" << xml.name() << xml.isStartElement();
    }
    return rules;
}
/*
 * TODO port to API v2
QVector< Echonest::SessionItem > Echonest::Parser::parseSessionSongItem( QXmlStreamReader& xml, const QString& type ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != type || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );

    QVector< Echonest::SessionItem > items;
    while( xml.name() == type && xml.isStartElement() ) {
//         qDebug() << "Parsing exernal item:" << xml.name() << xml.isStartElement();

        Echonest::SessionItem item;

        while( !xml.atEnd() && ( xml.name() != type || !xml.isEndElement() ) ) {
//             qDebug() << "Parsing internal item:" << xml.name() << xml.isStartElement();
            if( xml.name() == "served_time" )
                item.served_time = xml.readElementText().toDouble();
            else if( xml.name() == "artist_id" )
                item.artist_id = xml.readElementText().toLatin1();
            else if( xml.name() == "id" )
                item.id = xml.readElementText().toLatin1();
            else if( xml.name() == "artist_name" )
                item.artist_name= xml.readElementText();
            else if( xml.name() == "title" )
                item.title = xml.readElementText();
            else if( xml.name() == "rating" )
                item.rating = xml.readElementText().toInt();

            xml.readNextStartElement();
        }
        items.append( item );

        xml.readNext();
    }
    return items;
}*/

