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

#include <QNetworkReply>

void Echonest::Parser::checkForErrors( QNetworkReply* reply ) throw( Echonest::ParseError )
{   
    if( !reply )
        throw new ParseError( Echonest::UnknownError );
    
    if( !reply->isFinished() )
        throw new ParseError( Echonest::UnfinishedQuery );
    
    if( reply->error() != QNetworkReply::NoError ) {   
        ParseError* err = new ParseError( Echonest::NetworkError );
        err->setNetworkError( reply->error() );
        
        throw err;
    }
}

void Echonest::Parser::readStatus( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.readNextStartElement() ) {
        // sanity checks
        if( xml.name() !=  QLatin1String( "response" ) )
            throw new ParseError( UnknownParseError );
        
        if( xml.readNextStartElement() ) {
            if( xml.name() != "status" )
                throw new ParseError( UnknownParseError );
            
            // only check the error code for now
            xml.readNextStartElement();
            double version = xml.readElementText().toDouble();
            xml.readNextStartElement();
            Echonest::ErrorType code = static_cast< Echonest::ErrorType >( xml.readElementText().toInt() );
            xml.readNextStartElement();
            QString msg = xml.readElementText();
            xml.readNextStartElement();
            
            if( code != Echonest::NoError ) {
                throw new ParseError( code );
            }
            
            xml.readNext();
        }
        
    } else {
        throw new ParseError( UnknownParseError );
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
    if( xml.name() != "song" )
        throw new ParseError( Echonest::UnknownParseError );
    
    Echonest::Song song;   
    while( !( xml.name() == "song" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
        if( xml.name() == "id" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setId( xml.readElementText() );
        else if( xml.name() == "title" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setTitle( xml.readElementText() );
        else if( xml.name() == "artist_id" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setArtistId( xml.readElementText() );
        else if( xml.name() == "artist_name" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setArtistName( xml.readElementText() );
        else if( xml.name() == "song_hotttnesss" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setHotttnesss( xml.readElementText().toDouble() );
        else if( xml.name() == "artist_hotttnesss" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setArtistHotttnesss( xml.readElementText().toDouble() );
        else if( xml.name() == "artist_familiarity" && xml.tokenType() == QXmlStreamReader::StartElement )
            song.setArtistFamiliarity( xml.readElementText().toDouble() );
        else if( xml.name() == "artist_location" && xml.tokenType() == QXmlStreamReader::StartElement ) {
            while( !( xml.name() ==  "location" && xml.tokenType() == QXmlStreamReader::EndElement ) ) {
                xml.readNextStartElement();
                if( xml.name() == "location" )
                    song.setArtistLocation( xml.readElementText() );
            }
            xml.readNext();
        }
        // TODO tracks
        // TODO audio_summary
        xml.readNext();
    }
    xml.readNext(); // skip past the last </song>
    
    return song;
}

Echonest::Track Echonest::Parser::parseTrack( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    return Echonest::Track();
}