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
    
    if( reply->error() != QNetworkReply::NoError )
        throw new ParseError( (Echonest::ErrorType)reply->error() );
}

void Echonest::Parser::readStatus( QXmlStreamReader& xml ) throw( Echonest::ParseError )
{
    if( xml.readNextStartElement() ) {
        // sanity checks
        if( !( xml.name() ==  QLatin1String( "xml" ) && xml.attributes().value( QLatin1String( "encoding" ) ) == QLatin1String(  "UTF-8" ) ) )
            throw new ParseError( UnknownParseError );
        
        if( xml.readNextStartElement() ) {
            if( xml.name() != "status" )
                throw new ParseError( UnknownParseError );
            
            // only check the error code for now
            xml.readNextStartElement();
            double version = xml.readElementText().toDouble();
            
        }
        
    } else {
        throw new ParseError( UnknownParseError );
    }
}