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

#ifndef ECHONEST_CONFIG_H
#define ECHONEST_CONFIG_H

#include "echonest_export.h"

#include <QByteArray>
#include <QUrl>

class QNetworkAccessManager;

namespace Echonest{

    /// Creates the base URL for all GET and POST requests
    QUrl baseUrl();
    
    /// Creates the base URL for GET requests.
    QUrl baseGetQuery( const QByteArray& type, const QByteArray& method );
    
    class ConfigPrivate;
    /**
     * This singleton contains miscellaneous settings used to access The Echo Nest
     */
    class ECHONEST_EXPORT Config {        
    public:
        static Config* instance();
        
        /**
         * Set the API key to be used for all API requests. This MUST be set in order 
         *  for any web service calls to work!
         */
        void setAPIKey( const QByteArray& apiKey );
        QByteArray apiKey() const;
        
        /**
         * Set the QNetworkAccessManager to use to make web service requests to
         *  The Echo Nest.
         * 
         * This will take over control of the object.
         */
        void setNetworkAccessManager( QNetworkAccessManager* nam );
        QNetworkAccessManager* nam() const;
        
        
    private:
        Config();
        ~Config();
        
        static Config* s_instance;
        
        ConfigPrivate* d;
    };
    
}

#endif
