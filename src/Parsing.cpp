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

#include "Parsing_p.h"

#include "CatalogItem_p.h"
#include "Util.h"

#include <QNetworkReply>
#include "Artist.h"
#include <QDateTime>

void Echonest::Parser::checkForErrors( QNetworkReply* reply ) throw( Echonest::ParseError )
{   
    if( !reply )
        throw ParseError( Echonest::UnknownError );
    
    // TODO sometimes this returns false when it shouldn't be? what's going on..
//     if( !reply->isFinished() )
//         throw ParseError( Echonest::UnfinishedQuery );
//     
    if( reply->error() != QNetworkReply::NoError ) {   
        ParseError err(  Echonest::NetworkError );
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
            if( xml.atEnd() || xml.name() != "status" )
                throw ParseError( UnknownParseError );
            
            // only check the error code for now
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
                throw ParseError( code );
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
    while( !( xml.name() == "songs" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        // parse a song
        songs.append( parseSong( xml ) );
    }
    return songs;
}

Echonest::Song Echonest::Parser::parseSong( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "song" )
        throw ParseError( Echonest::UnknownParseError );
    
    Echonest::Song song;   
    while( !( xml.name() == "song" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == "id" && xml.isStartElement() )
            song.setId( xml.readElementText().toLatin1() );
        else if( xml.name() == "title" && xml.isStartElement() )
            song.setTitle( xml.readElementText() );
        else if( xml.name() == "artist_id" && xml.isStartElement() )
            song.setArtistId( xml.readElementText().toLatin1() );
        else if( xml.name() == "artist_name" && xml.isStartElement() )
            song.setArtistName( xml.readElementText() );
        else if( xml.name() == "song_hotttnesss" && xml.isStartElement() )
            song.setHotttnesss( xml.readElementText().toDouble() );
        else if( xml.name() == "artist_hotttnesss" && xml.isStartElement() )
            song.setArtistHotttnesss( xml.readElementText().toDouble() );
        else if( xml.name() == "artist_familiarity" && xml.isStartElement() )
            song.setArtistFamiliarity( xml.readElementText().toDouble() );
        else if( xml.name() == "artist_location" && xml.isStartElement() ) {
            while( !( xml.name() ==  "location" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
                xml.readNextStartElement();
                if( xml.name() == "location" )
                    song.setArtistLocation( xml.readElementText() );
            }
            xml.readNext();
        } else if( xml.name() == "audio_summary" && xml.isStartElement() ) {
            song.setAudioSummary( parseAudioSummary( xml ) );
        }
        xml.readNext();
    }
    xml.readNext(); // skip past the last </song>
    
    return song;
}

Echonest::Track Echonest::Parser::parseTrack( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "track" ) {
        throw ParseError( Echonest::UnknownParseError );
    }
    
    Echonest::Track track;
    while( !( xml.name() == "track" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == "id" && xml.isStartElement() )
            track.setId( xml.readElementText().toLatin1() );
        else if( xml.name() == "title" && xml.isStartElement() )
            track.setTitle( xml.readElementText() );
        else if( xml.name() == "artist" && xml.isStartElement() )
            track.setArtist( xml.readElementText() );
        else if( xml.name() == "status" && xml.isStartElement() )
            track.setStatus( Echonest::statusToEnum( xml.readElementText() ) );
        else if( xml.name() == "analyzer_version" && xml.isStartElement() )
            track.setAnalyzerVersion( xml.readElementText() );
        else if( xml.name() == "release" && xml.isStartElement() )
            track.setRelease( xml.readElementText() );
        else if( xml.name() == "audio_md5" && xml.isStartElement() )
            track.setAudioMD5( xml.readElementText().toLatin1() );
        else if( xml.name() == "bitrate" && xml.isStartElement() )
            track.setBitrate( xml.readElementText().toInt() );
        else if( xml.name() == "samplerate" && xml.isStartElement() )
            track.setSamplerate( xml.readElementText().toInt() );
        else if( xml.name() == "md5" && xml.isStartElement() )
            track.setMD5( xml.readElementText().toLatin1() );
        else if( xml.name() == "audio_summary" && xml.isStartElement() ) {
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
    if( xml.atEnd() || xml.name() != "audio_summary" ) {
        throw ParseError( Echonest::UnknownParseError );
    }
    
    Echonest::AudioSummary summary;
    while( !( xml.name() == "audio_summary" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == "key" && xml.isStartElement() )
            summary.setKey( xml.readElementText().toInt() );
        else if( xml.name() == "analysis_url" && xml.isStartElement() )
            summary.setAnalysisUrl( xml.readElementText() );
        else if( xml.name() == "tempo" && xml.isStartElement() )
            summary.setTempo( xml.readElementText().toDouble() );
        else if( xml.name() == "mode" && xml.isStartElement() )
            summary.setMode( xml.readElementText().toInt() );
        else if( xml.name() == "time_signature" && xml.isStartElement() )
            summary.setTimeSignature( xml.readElementText().toInt() );
        else if( xml.name() == "duration" && xml.isStartElement() )
            summary.setDuration( xml.readElementText().toDouble() );
        else if( xml.name() == "loudness" && xml.isStartElement() )
            summary.setLoudness( xml.readElementText().toDouble() );
        else if( xml.name() == "danceability" && xml.isStartElement() )
            summary.setDanceability( xml.readElementText().toDouble() );
        else if( xml.name() == "energy" && xml.isStartElement() )
            summary.setEnergy( xml.readElementText().toDouble() );
        
        xml.readNext();
    }
    
    return summary;
}


Echonest::Artists Echonest::Parser::parseArtists( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    // we expect to be in an <artists> start element
    if( xml.atEnd() || xml.name() != "artists" || !xml.isStartElement() )
        throw ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    
    Echonest::Artists artists;
    while( !xml.atEnd() && ( xml.name() != "artists" || !xml.isEndElement() ) ) {
        if( xml.atEnd() || xml.name() != "artist" || !xml.isStartElement() )
            throw Echonest::ParseError( Echonest::UnknownParseError );
        Echonest::Artist artist;
        while( !xml.atEnd() && ( xml.name() != "artist" || !xml.isEndElement() ) ) {
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
    if( xml.name() == "start" ) { // this is an individual info query, so lets read it
        xml.readNextStartElement();
        xml.readNext();
        
        int results = -1;
        if( xml.name() == "total" ) {
            results = xml.readElementText().toInt();
            xml.readNextStartElement();
        }
        
        parseArtistInfo( xml, artist );
        
        return results;
    } else if( xml.name() == "songs" ) {
        parseArtistSong( xml, artist );
    } else if( xml.name() == "urls" ) { // urls also has no start/total
        parseUrls( xml, artist );  
    } else { // this is either a profile query, or a familiarity or hotttness query, so save all the data we find
        while( !( xml.name() == "artist" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
            parseArtistInfo( xml, artist );
            xml.readNextStartElement();
        }
    }
    
    return 0;
}

void Echonest::Parser::parseArtistInfo( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    // parse each sort of artist information
    if( xml.name() == "audio" ) {
        parseAudio( xml, artist );
    } else if( xml.name() == "biographies" ) {
        parseBiographies( xml, artist );
    } else if( xml.name() == "familiarity" ) {
        artist.setFamiliarity( xml.readElementText().toDouble() );
    }  else if( xml.name() == "hotttnesss" ) {
        artist.setHotttnesss( xml.readElementText().toDouble() );
    }  else if( xml.name() == "images" ) {
        parseImages( xml, artist );
    }  else if( xml.name() == "news" && xml.isStartElement() ) {
        parseNewsOrBlogs( xml, artist, true );
    }  else if( xml.name() == "blogs" ) {
        parseNewsOrBlogs( xml, artist, false );
    }  else if( xml.name() == "reviews" ) {
        parseReviews( xml, artist );
    }  else if( xml.name() == "terms" ) {
        parseTerms( xml, artist );
    }  else if( xml.name() == "urls" ) {
        parseTerms( xml, artist );
    }  else if( xml.name() == "songs" ) {
        parseArtistSong( xml, artist );
    }  else if( xml.name() == "video" ) {
        parseVideos( xml, artist );
    }  else if( xml.name() == "foreign_ids" ) {
        parseForeignIds( xml, artist );
    }  else if( xml.name() == "name" ) {
        artist.setName( xml.readElementText() );
    }  else if( xml.name() == "id" ) {
        artist.setId( xml.readElementText().toLatin1() );
    } 
}


// parse each type of artist attribute

void Echonest::Parser::parseAudio( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "audio" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    Echonest::AudioList audioList;
    while( !xml.atEnd() && ( xml.name() != "audio" || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::AudioFile audio;
        do {
            xml.readNext();
            
            if( xml.name() == "title" )
                audio.setTitle( xml.readElementText() );
            else if( xml.name() == "url" )
                audio.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "artist" )
                audio.setArtist(  xml.readElementText() );
            else if( xml.name() == "date" )
                audio.setDate( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == "length" )
                audio.setLength( xml.readElementText().toDouble() );
            else if( xml.name() == "link" )
                audio.setLink( QUrl( xml.readElementText() ) );
            else if( xml.name() == "release" )
                audio.setRelease( xml.readElementText() );
            else if( xml.name() == "id" )
                audio.setId( xml.readElementText().toLatin1() );
            
        } while( !xml.atEnd() && ( xml.name() != "audio" || xml.tokenType() != QXmlStreamReader::EndElement ) );
        audioList.append( audio );
        xml.readNext();
    }
    artist.setAudio( audioList );
}

void Echonest::Parser::parseBiographies( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "biographies" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    Echonest::BiographyList bios;
    while( !xml.atEnd() && ( xml.name() != "biographies" || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::Biography bio;
        do {
            xml.readNext();
            
            if( xml.name() == "text" )
                bio.setText( xml.readElementText() );
            else if( xml.name() == "site" )
                bio.setSite( xml.readElementText() );
            else if( xml.name() == "url" )
                bio.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "license" )
                bio.setLicense( parseLicense( xml) );
            
        } while( !xml.atEnd() && ( xml.name() != "biography" || xml.tokenType() != QXmlStreamReader::EndElement ) );
        bios.append( bio );
        xml.readNext();
    }
    artist.setBiographies( bios );
}


void Echonest::Parser::parseImages( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "images" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    Echonest::ArtistImageList imgs;
    while( !xml.atEnd() && ( xml.name() != "images" || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::ArtistImage img;
        do {
            xml.readNext();
            
            if( xml.name() == "url" )
                img.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "license" )
                img.setLicense( parseLicense( xml) );
            
        } while( !xml.atEnd() && ( xml.name() != "image" || xml.tokenType() != QXmlStreamReader::EndElement ) );
        imgs.append( img );
        xml.readNext();
    }
    artist.setImages( imgs );
}

void Echonest::Parser::parseNewsOrBlogs( QXmlStreamReader& xml, Echonest::Artist& artist, bool news  ) throw( Echonest::ParseError )
{
    if( news && ( xml.atEnd() || xml.name() != "news" || xml.tokenType() != QXmlStreamReader::StartElement ) )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    else if( !news && ( xml.atEnd() || xml.name() != "blogs" || xml.tokenType() != QXmlStreamReader::StartElement ) )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    Echonest::NewsList newsList;
    while( !( ( xml.name() == "news" || xml.name() == "blogs" ) && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        Echonest::NewsArticle news;
        do {
            xml.readNextStartElement();
            
            if( xml.name() == "name" )
                news.setName( xml.readElementText() );
            else if( xml.name() == "url" )
                news.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "summary" )
                news.setSummary(  xml.readElementText() );
            else if( xml.name() == "date_found" )
                news.setDateFound( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == "id" )
                news.setId( xml.readElementText().toLatin1() );
            else if( xml.name() == "date_posted" )
                news.setDatePosted( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
        } while( !( ( xml.name() == "news" || xml.name() == "blog" ) && xml.tokenType() == QXmlStreamReader::EndElement ) );
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
    if( xml.atEnd() || xml.name() != "reviews" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    Echonest::ReviewList reviews;
    while( !xml.atEnd() && ( xml.name() != "reviews" || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        Echonest::Review review;
        do {
            xml.readNextStartElement();
            
            if( xml.name() == "url" )
                review.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "name" )
                review.setName( xml.readElementText() );
            else if( xml.name() == "summary" )
                review.setSummary( xml.readElementText() );
            else if( xml.name() == "date_found" )
                review.setDateFound( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == "image" )
                review.setImageUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "release" )
                review.setRelease( xml.readElementText() );
            else if( xml.name() == "id" )
                review.setId( xml.readElementText().toLatin1() );
            
        } while( !xml.atEnd() && ( xml.name() != "review" || xml.tokenType() != QXmlStreamReader::EndElement ) );
        reviews.append( review );
        xml.readNext();
    }
    artist.setReviews( reviews );
}

void Echonest::Parser::parseArtistSong( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "songs" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    xml.readNextStartElement();
    Echonest::SongList songs;
    while( !xml.atEnd() && ( xml.name() != "songs" || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        if( xml.name() == "song" && xml.isStartElement() ) 
        {
            Echonest::Song song;
            while( !xml.atEnd() && ( xml.name() != "song" || !xml.isEndElement() ) ) {
                if( xml.name() == "id" && xml.isStartElement() )
                    song.setId( xml.readElementText().toLatin1() );
                else if( xml.name() == "title" && xml.isStartElement() )
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
    if( xml.atEnd() || xml.name() != "terms" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    artist.setTerms( parseTermList( xml ) );
}

void Echonest::Parser::parseUrls( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "urls" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    xml.readNextStartElement();
//     xml.readNextStartElement();
    
    while( !xml.atEnd() && ( xml.name() != "urls" || !xml.isEndElement() ) ) {
        if( xml.name() == "lastfm_url" )
            artist.setLastFmUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == "aolmusic_url" )
            artist.setAolMusicUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == "myspace_url" )
            artist.setMyspaceUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == "amazon_url" )
            artist.setAmazonUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == "itunes_url" )
            artist.setItunesUrl( QUrl( xml.readElementText() ) );
        else if( xml.name() == "mb_url" )
            artist.setMusicbrainzUrl( QUrl( xml.readElementText() ) );
        
        xml.readNextStartElement();
    }
    xml.readNextStartElement();
}

void Echonest::Parser::parseVideos( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "video" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    Echonest::VideoList videos;
    while( xml.name() == "video" && xml.isStartElement() ) {
        
        Echonest::Video video;
        
        while( !xml.atEnd() && ( xml.name() != "video" || !xml.isEndElement() ) ) {
            if( xml.name() == "title" )
                video.setTitle( xml.readElementText() );
            else if( xml.name() == "url" )
                video.setUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "site" )
                video.setSite( xml.readElementText() );
            else if( xml.name() == "date_found" )
                video.setDateFound( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
            else if( xml.name() == "image_url" )
                video.setImageUrl( QUrl( xml.readElementText() ) );
            else if( xml.name() == "id" )
                video.setId( xml.readElementText().toLatin1() );
            
            xml.readNextStartElement();
        }
        videos.append( video );
        
        xml.readNextStartElement();
    }
    artist.setVideos( videos );
}

Echonest::TermList Echonest::Parser::parseTermList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "terms" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    Echonest::TermList terms;
    while( xml.name() == "terms" && xml.isStartElement() ) {
        
        Echonest::Term term;
        
        while( !xml.atEnd() && ( xml.name() != "terms" || !xml.isEndElement() ) ) {
            if( xml.name() == "frequency" )
                term.setFrequency( xml.readElementText().toDouble() );
            else if( xml.name() == "name" )
                term.setName( xml.readElementText() );
            else if( xml.name() == "weight" )
                term.setWeight( xml.readElementText().toDouble() );
            
            xml.readNextStartElement();
        }
        terms.append( term );
        
        xml.readNext();
    }
    return terms;
}

void Echonest::Parser::parseForeignIds( QXmlStreamReader& xml, Echonest::Artist& artist ) throw( Echonest::ParseError )
{

}

Echonest::License Echonest::Parser::parseLicense( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "license" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    Echonest::License license;
    while( !xml.atEnd() && ( xml.name() != "license" || xml.tokenType() != QXmlStreamReader::EndElement ) ) {
        if( xml.name() == "type" )
            license.type = xml.readElementText();
        else if( xml.name() == "attribution" )
            license.attribution = xml.readElementText();
        else if( xml.name() == "url" )
            license.url = QUrl( xml.readElementText() );
        
        xml.readNext();
    }
    
    xml.readNextStartElement();
    return license;
}

QByteArray Echonest::Parser::parsePlaylistSessionId( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "session_id" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    QByteArray sessionId = xml.readElementText().toLatin1();
    xml.readNext(); //read to next start element
    return sessionId;
}

// Catalogs parseCatalogList( QXmlStreamReader& xml ) throw( ParseError );
Echonest::Catalogs Echonest::Parser::parseCatalogList( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    int start = -1;
    int total = -1;
    while( xml.name() != "response" && ( xml.name() != QLatin1String( "catalogs" ) || !xml.isStartElement() ) ) {
        if( xml.name() == "start" && xml.isStartElement() )
            start = xml.readElementText().toInt();
        else if( xml.name() == "total" && xml.isStartElement() )
            total = xml.readElementText().toInt();
        xml.readNextStartElement();
    }
    
        
    Echonest::Catalogs catalogs;
    
    if( xml.name() != "catalogs" ) { // none
        return catalogs;
    }

    catalogs.reserve( total );
    // now we're pointing at the first catalog
    while( xml.name() != "response" || !xml.isEndElement() )
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
        if( xml.name() == "total" && xml.isStartElement() )
            catalog.setTotal( xml.readElementText().toInt() );
        else if( xml.name() == "type" && xml.isStartElement() )
            catalog.setType( Echonest::literalToCatalogType( xml.readElementText().toLatin1() ) );
        else if( xml.name() == "id" && xml.isStartElement() )
            catalog.setId( xml.readElementText().toLatin1() );
        else if( xml.name() == "name" && xml.isStartElement() )
            catalog.setName( xml.readElementText() );
        else if( xml.name() == "items" && xml.isStartElement() ) {
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
    if( xml.atEnd() || xml.name() != "items" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    QList<Echonest::CatalogItem*> items;
    while( xml.name() == "items" && xml.isStartElement() ) {
        // OK, the mixture of the crappy Catalog API and strongly typed c++ makes this ugly. We don't know if this is an artist or song until we reach the artist_id or song_id.
        //  so, we'll keep two copies till the end, where we throw away one. :(
        Echonest::CatalogArtist* artist = new Echonest::CatalogArtist;
        Echonest::CatalogSong* song = new CatalogSong;
        while( xml.name() != "items" || !xml.isEndElement() ) {
            // OK, we have to check for all possible song+artist types :'(
            if( xml.name() == "rating" && xml.isStartElement() ) { /// mixed and artist items
                artist->setRating( xml.readElementText().toInt() );
                song->setRating( artist->rating() );
            } else if( xml.name() == "request" && xml.isStartElement() ) {
                parseCatalogRequestItem( xml, *artist, *song );
            } else if( xml.name() == "artist_name" && xml.isStartElement() ) {
                artist->setName( xml.readElementText() );
                song->setArtistName( artist->name() );
            } else if( xml.name() == "reviews" && xml.isStartElement() ) {
                parseReviews( xml, *artist );
            } else if( xml.name() == "terms" && xml.isStartElement() ) {
                parseTerms( xml, *artist );
                continue;
            } else if( xml.name() == "biographies" && xml.isStartElement() ) {
                parseBiographies( xml, *artist );
            } else if( xml.name() == "familiarity" && xml.isStartElement() ) {
                artist->setFamiliarity( xml.readElementText().toDouble() );
                song->setArtistFamiliarity( artist->familiarity() );
            } else if( xml.name() == "blogs" && xml.isStartElement() ) {
                parseNewsOrBlogs( xml, *artist, false );
            } else if( xml.name() == "hotttnesss" && xml.isStartElement() ) {
                artist->setHotttnesss( xml.readElementText().toDouble() );
                song->setArtistHotttnesss( artist->hotttnesss() );
            } else if( xml.name() == "video" && xml.isStartElement() ) {
                parseVideos( xml, *artist );
            } else if( xml.name() == "urls" && xml.isStartElement() ) {
                parseUrls( xml, *artist );
            } else if( xml.name() == "news" && xml.isStartElement() ) {
                parseNewsOrBlogs( xml, *artist );
            } else if( xml.name() == "images" && xml.isStartElement() ) {
                parseImages( xml, *artist );
            } else if( xml.name() == "date_added" && xml.isStartElement() ) {
                artist->setDateAdded( QDateTime::fromString( xml.readElementText(), Qt::ISODate ) );
                song->setDateAdded( artist->dateAdded() );
            } else if( xml.name() == "artist_id" && xml.isStartElement() ) {
                artist->setId( xml.readElementText().toLatin1() );
                song->setArtistId( artist->id() );
            } else if( xml.name() == "audio" && xml.isStartElement() ) {
                parseAudio( xml, *artist );
            } else if( xml.name() == "foreign_id" && xml.isStartElement() ) {
                artist->setForeignId( xml.readElementText().toLatin1()  );
                song->setForeignId( artist->foreignId() );
            } else if( xml.name() == "song_id" && xml.isStartElement() ) { /// song-specific entries
                song->setId( xml.readElementText().toLatin1() );
            } else if( xml.name() == "song_name" && xml.isStartElement() ) {
                song->setTitle( xml.readElementText() );
            } else if( xml.name() == "tracks" && xml.isStartElement() ) {
//                 parseS( xml, *artist ); TODO
            } else if( xml.name() == "play_count" && xml.isStartElement() ) {
               static_cast<Echonest::CatalogSong*>(song)->setPlayCount( xml.readElementText().toInt() );
            } else if( xml.name() == "artist_hotttnesss" && xml.isStartElement() ) {
                song->setArtistHotttnesss( xml.readElementText().toDouble() );
            } else if( xml.name() == "artist_location" && xml.isStartElement() ) {
                // TODO
            } else if( xml.name() == "song_hotttnesss" && xml.isStartElement() ) {
                song->setHotttnesss( xml.readElementText().toDouble() );
            } else if( xml.name() == "artist_familiarity" && xml.isStartElement() ) {
                song->setArtistFamiliarity( xml.readElementText().toDouble() );
            } else if( xml.name() == "audio_summary" && xml.isStartElement() ) {
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
    if( xml.atEnd() || xml.name() != "request" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    while( xml.name() != "request" || !xml.isEndElement() ) {
        if( xml.name() == "item_id" ) {
            artist.setRequestId( xml.readElementText().toLatin1() );
            song.setRequestId( artist.requestId() );
        } else if( xml.name() == "artist_name" ) {
            artist.setRequestName( xml.readElementText() );
            song.setRequestName( artist.requestName() );
        } else if( xml.name() == "song_name" ) {
            artist.setRequestName( xml.readElementText() );
            song.setRequestName( artist.requestName() );
        }
        // TODO finish
        xml.readNext();
    }
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
    if( xml.atEnd() || xml.name() != "ticket_status" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    Echonest::CatalogStatus status;
    
    while( xml.name() != "response" || !xml.isEndElement() ) {
        if( xml.name() == "ticket_status" && xml.isStartElement() )
            status.status = Echonest::literalToCatalogStatus( xml.readElementText().toLatin1() );
        else if( xml.name() == "items_updated" && xml.isStartElement() )
            status.items_updated = xml.readElementText().toInt();
        else if( xml.name() == "update_info" && xml.isStartElement() )
            status.items = parseTicketUpdateInfo( xml );
        
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
    if( xml.atEnd() || xml.name() != "ticket" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    QByteArray ticket= xml.readElementText().toLatin1();
    return ticket;
}

Echonest::Catalog Echonest::Parser::parseNewCatalog( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.atEnd() || xml.name() != "name" || xml.tokenType() != QXmlStreamReader::StartElement )
        throw Echonest::ParseError( Echonest::UnknownParseError );
    
    QString name;
    QByteArray id;
    Echonest::CatalogTypes::Type type = Echonest::CatalogTypes::Artist;
    
    while( xml.name() != "response" || !xml.isEndElement() ) {
        if( xml.name() == "name" && xml.isStartElement() )
            name = xml.readElementText();
        else if( xml.name() == "id" && xml.isStartElement() )
            id = xml.readElementText().toLatin1();
        else if( xml.name() == "type" && xml.isStartElement() )
            type = Echonest::literalToCatalogType( xml.readElementText().toLatin1() );
        
        xml.readNextStartElement();
    }
    Echonest::Catalog c = Echonest::Catalog( id );
    c.setName( name );
    c.setType( type );
    
    return c;
}


