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


#ifndef ECHONEST_PLAYLIST_H
#define ECHONEST_PLAYLIST_H

#include "echonest_export.h"
#include "Song.h"

#include <QSharedData>
#include <QDebug>
#include "Artist.h"
#include <QtCore/QString>
#include "Catalog.h"

class QNetworkReply;
class DynamicPlaylistData;

namespace Echonest{

    typedef struct {
        QByteArray session_id;
        Artists banned_artists;
        Artists favorited_artists;
        SongList banned_songs;
        SongList favorited_songs;
        QVariantMap options;
        QVariantMap ratingsMap;
        // TODO favorites_map
        // TODO constraints
        
    } SessionInfo;
    
    /**
     * This encapsulates an Echo Nest dynamic playlist. It contains a playlist ID and
     *  the current song, and can fetch the next song.
     *
     *  See http://developer.echonest.com/docs/v4/playlist.html#dynamic
     *   for more information
     */
    class ECHONEST_EXPORT DynamicPlaylist
    {
    public:
        /**
         * The types of playlist that can be generated. Artist plays songs for the given artist,
         *  ArtistRadio takes into account similar artists, and ArtistDescription plays songs matching
         *  the given description.
         */
        enum ArtistTypeEnum {
            ArtistType,
            ArtistRadioType,
            ArtistDescriptionType,
            CatalogType,
            CatalogRadioType,
            SongRadioType
        };

        /**
         * Different ways to sort a generated playlist
         */
        enum SortingType {
            SortTempoAscending,
            SortTempoDescending,
            SortDurationAscending,
            SortDurationDescending,
            SortArtistFamiliarityAscending,
            SortArtistFamiliarityDescending,
            SortArtistHotttnessAscending,
            SortArtistHotttnessDescending,
            SortSongHotttnesssAscending,
            SortSongHotttnesssDescending,
            SortLatitudeAscending,
            SortLatitudeDescending,
            SortLongitudeAscending,
            SortLongitudeDescending,
            SortModeAscending,
            SortModeDescending,
            SortKeyAscending,
            SortKeyDescending,
            SortLoudnessAscending,
            SortLoudnessDescending,
            SortEnergyAscending,
            SortEnergyDescending,
            SortDanceabilityAscending,
            SortDanceabilityDescending
        };

        /**
         * Different ways of picking artists in Artist radios.
         */
        enum ArtistPick {
            PickSongHotttnesssAscending,
            PickTempoAscending,
            PickDurationAscending,
            PickLoudnessAscending,
            PickModeAscending,
            PickKeyAscending,
            PickSongHotttnesssDescending,
            PickTempoDescending,
            PickDurationDescending,
            PickLoudnessDescending,
            PickModeDescending,
            PickKeyDescending
        };

        /**
         * The various parameters that can be passed to the playlist building
         *  functions.
         */
        enum PlaylistParam {
            Type, /// The type of playlist to generate. Value is the DynamicPlaylist::ArtistTypeEnum enum
            Format, /// Either xml (default) or xspf. If the result is xspf, the raw xspf playlist is returned, else the xml is parsed and exposed programmatically. If using XSPF, you must specify a catalog, the tracks bucket, and limit = true
            Pick,   /// How the artists are picked for each artist in ArtistType playlists. Value is Playlist::ArtistPick enum value.
            Variety, /// 0 < variety < 1        The maximum variety of artists to be represented in the playlist. A higher number will allow for more variety in the artists.
            ArtistId, ///  ID(s) of seed artist(s) for the playlist
            Artist, /// Artist names of seeds for playlist
            ArtistSeedCatalog, /// ID of seed artist catalog for the playlist
            SourceCatalog, /// ID of catalog (artist or song) for catalog type playlists
            SongId, /// IDs of seed songs for the playlist
            Description, /// Textual description for sort of songs that can be included in the playlist
            Results, /// 0-100, how many sonsg to include in the playlist, default 15
            MaxTempo, /// 0.0 < tempo < 500.0 (BPM)       The maximum tempo for any included songs
            MinTempo, /// 0.0 < tempo < 500.0 (BPM)       the minimum tempo for any included songs
            MaxDuration, /// 0.0 < duration < 3600.0 (seconds)       the maximum duration of any song on the playlist
            MinDuration, /// 0.0 < duration < 3600.0 (seconds)       the minimum duration of any song on the playlist
            MaxLoudness, /// -100.0 < loudness < 100.0 (dB)  the maximum loudness of any song on the playlist
            MinLoudness, /// -100.0 < loudness < 100.0 (dB)  the minimum loudness of any song on the playlist
            MinDanceability, /// 0 < danceability < 1  a measure of the minimum danceability of the song
            MaxDanceability, /// 0 < danceability < 1  a measure of the maximum danceability of the song
            MinEnergy, /// 0 < danceability < 1  a measure of the maximum energy of the song
            MaxEnergy, /// 0 < danceability < 1  a measure of the maximum energy of the song
            ArtistMaxFamiliarity, ///  0.0 < familiarity < 1.0 the maximum artist familiarity for songs in the playlist
            ArtistMinFamiliarity, ///  0.0 < familiarity < 1.0 the minimum artist familiarity for songs in the playlist
            ArtistMaxHotttnesss, ///  0.0 < hotttnesss < 1.0  the maximum hotttnesss for artists in the playlist
            ArtistMinHotttnesss, ///  0.0 < hotttnesss < 1.0  the maximum hotttnesss for artists in the playlist
            SongMaxHotttnesss, ///  0.0 < hotttnesss < 1.0  the maximum hotttnesss for songs in the playlist
            SongMinHotttnesss, ///  0.0 < hotttnesss < 1.0  the maximum hotttnesss for songs in the playlist
            ArtistMinLongitude, /// -180.0 < longitude < 180.0      the minimum longitude for the location of artists in the playlist
            ArtistMaxLongitude, /// -180.0 < longitude < 180.0      the maximum longitude for the location of artists in the playlist
            ArtistMinLatitude,  /// -90.0 < latitude < 90.0 the minimum latitude for the location of artists in the playlist
            ArtistMaxLatitude, /// -90.0 < latitude < 90.0 the maximum latitude for the location of artists in the playlist
            Mode, /// (minor, major) 0, 1     the mode of songs in the playlist
            Key, /// (c, c-sharp, d, e-flat, e, f, f-sharp, g, a-flat, a, b-flat, b) 0 - 11  the key of songs in the playlist
            SongInformation, /// what sort of song information should be returned. Should be an Echonest::SongInformation object
            Sort, /// SortingType enum, the type of sorting to use,
            Limit, /// true, false    if true songs will be limited to those that appear in the catalog specified by the id: bucket
            Audio, /// true, false,  if true songs will be limited to those that have associated audio
            DMCA, /// true, false    Only valid for dynamic playlists. Sets if playlist will follow DMCA rules (see web api doc for details)
            ChainXSPF, /// true, false    If true, returns an xspf for this dynamic playlist with 2 items. The second item will be a link to the API call for the next track in the chain. Please note that this sidesteps libechonest's handling of the tracks.
            Mood, /// A mood to limit this playlist to, for example "happy" or "sad". Multiples of this param are okay. See the method Artist::listTerms for details on what moods are currently available
            Style, /// A style to limit this playlist to, for example "happy" or "sad". Multiples of this param are okay. See the method Artist::listTerms for details on what styles are currently available
            Adventurousness, /// A value of 0 means no adventurousness, only known and preferred music will be played. A value of 1 means high adventurousness, mostly unknown music will be played. This parameter only applies to catalog and catalog-radio type playlists.
            MoreLikeThis, /// When steering: Supply a song id to steer this session towards. Can be boosted from 0-5 like so: SO12341234^2. Default is 1
            LessLikeThis, /// When steering: Supply a song id to steer this session away from. Can be boosted from 0-5 like so: SO12341234^2. Default is 1
            TargetTempo, /// When steering: 0.0 < tempo < 500. (BPM). Target a desired tempo for the songs in this dynamic playlist session
            TargetLoudness, /// When steering: -100. < loudness < 100. (BPM)dB. Target a desired loudness for the songs in this dynamic playlist session
            TargetDanceability, /// When steering: 0.0 < danceability < 1. Target a desired danceability for the songs in this dynamic playlist session
            TargetEnergy, /// When steering: 0.0 < energy < 1.Target a desired energy for the songs in this dynamic playlist session
            TargetSongHotttnesss, /// When steering: 0.0 < song_hotttnesss < 1.Target a desired song_hotttnesss for the songs in this dynamic playlist session
            TargetArtistHotttnesss, /// When steering: 0.0 < artist_hottttnesss < 1.Target a desired artist_hottttnesss for the songs in this dynamic playlist session
            TargetArtistFamiliarity, /// When steering: 0.0 < artist_familiarity < 1.Target a desired energy for the artist_familiarity in this dynamic playlist session
        };

        /**
         * The types of feedback that can be used to steer a dynamic playlist
         */
        enum DynamicFeedbackParam {
            BanArtist, /// Ban this artist from this dynamic session. [artist_id, track_id, song_id, "last"]
            FavoriteArtist, /// Mark this artist as 'liked' for this session. [artist_id, track_id, song_id, "last"]
            BanSong, /// Ban this song from this dynamic session. [track_id, song_id, "last"]
            SkipSong, /// Mark this song as skipped by the user. Will not appear for the rest of the session. [track_id, song_id, "last"]
            FavoriteSong, /// Mark this song as a favorite. [track_id, song_id, "last"]
            PlaySong, /// Mark this song as played. Unneeded unless you want to pre-seed a station. [track_id, song_id, "last"]
            UnplaySong, /// Remove a song from a dynamic session's history. Will not blacklist the song. [track_id, song_id, "last"]
            RateSong, /// Rate the desired song. [track_id, song_id, "last"]^[0-10]. E.g: "last^3" or "TRTLKZV12E5AC92E11^5"
        };

        typedef QPair< PlaylistParam, QVariant > PlaylistParamData;
        typedef QVector< PlaylistParamData > PlaylistParams;

        typedef QPair< DynamicFeedbackParam, QByteArray > DynamicFeedbackParamData;
        typedef QVector< DynamicFeedbackParamData > DynamicFeedback;
        
        /**
         * The various controls for a dynamic playlist.
         *
         * Please see The Echo Nest API documentation for more information
         */
        enum DynamicControlItem {
          Steer = 0,
          SteerDescription,
          Rating,
          Ban
        };
        typedef QPair< DynamicControlItem, QString > DynamicControl;
        typedef QVector< DynamicControl > DynamicControls;

        DynamicPlaylist();
        virtual ~DynamicPlaylist();
        DynamicPlaylist( const DynamicPlaylist& other );
        DynamicPlaylist& operator=( const DynamicPlaylist& playlist );

        /**
         * Start a dynamic playlist with the given parameters.
         *  Once the QNetworkReply has finished, pass it to parseStart()
         *
         *  To fetch tracks, call fetchNextSong(). The info() method can be used
         *   to extract session information
         */
        QNetworkReply* create( const PlaylistParams& params ) const;
        void parseCreate( QNetworkReply* ) throw( ParseError );

        /**
         * Retart a dynamic playlist with the given parameters.
         *  Once the QNetworkReply has finished, pass it to parseStart()
         *
         * This is the same as start(), except it maintains the history from an
         *  already-existing playing station.
         */
        QNetworkReply* restart( const PlaylistParams& params ) const;

        /**
         * The session id of this dynamic playlist. If the playlist has ended, or has not been started,
         *  the result is empty.
         *
         */
        QByteArray sessionId() const;
        void setSessionId( const QByteArray& id );

        /**
         * The current song of this dynamic playlist. Once this song has been played,
         *  or whenever is desired, call fetchNextSong() to get the next song.
         */
        Song currentSong() const;
        void setCurrentSong( const Song& song );

        /**
         * Queries The Echo Nest for the next playable song(s) in this
         *  dynamic playlist.
         *
         * \param @results How many results to return, 1-5. This lets you
         *                 reduce the calls if you need more than one. Default is 1.
         * \param @lookahead The potential next songs (after the results)
         *                   if there is no steering applied. 0-5, default of 0.
         */
        QNetworkReply* next( int results = 1, int lookahead = 0 ) const;

        /**
         * Return the result of a dynamic/next API call. This will return two lists:
         * the "next" list and the "lookahead" list. Consult the \ref next() docs
         * and The Echo Nest documentation for more information.
         */
        QPair<SongList, SongList> parseNext( QNetworkReply* reply ) throw( ParseError );

        /**
         * Returns feedback to The Echo Nest for the currently playing dynamic
         *  playlist.
         *
         * See The Echo Nest api documentation for complete details.
         *
         * \param feedback A list of feedback items to apply.
         */
        QNetworkReply* feedback(const DynamicFeedback& feedback) const;

        /**
         * Parses the result of the feedback call.
         *
         * Will throw an exception if the return code is not successful (as other parse methods do).
         */
        void parseFeedback(QNetworkReply* reply) const throw( ParseError );

        /**
         * Modifies the upcoming tracks in this dynamic playlist session by steering it.
         *
         * Steering is additive, and can be reset for a dynamic playlist by calling reset.
         *
         * \param steerParams The desired steering params. Only use the enum values that correspond to valid steering commands.
         */
        QNetworkReply* steer(const PlaylistParams& steerParams) const;

        /**
         * Parses the result of the steer call.
         *
         * Will throw an exception if the return code is not successful (as other parse methods do).
         */
        void parseSteer(QNetworkReply* reply) const throw( ParseError );

        /**
         * Returns a description of this dynamic playlist session
         */
        QNetworkReply* fetchInfo() const;
        SessionInfo parseInfo( QNetworkReply* reply ) throw( ParseError );

        /**
         * Deletes a currently active playlist session. A non-commercial API can have, at most 1,000 active playlist sessions.
         */
        QNetworkReply* deleteSession() const;
        void parseDeleteSession(QNetworkReply* reply);
        
        /**
         * Generate a static playlist, according to the desired criteria. Use parseXSPFPlaylist if
         *  you pass format=xspf to \c staticPlaylist().
         */
        static QNetworkReply* staticPlaylist( const PlaylistParams& params );
        static SongList parseStaticPlaylist( QNetworkReply* reply ) throw( ParseError );

        /**
         * Parse an xspf playlist. Returns the full xspf content with no modifications.
         */
        static QByteArray parseXSPFPlaylist( QNetworkReply* reply ) throw( ParseError );

    private:
        static QByteArray playlistParamToString( PlaylistParam param );
        static QNetworkReply* generateInternal( const PlaylistParams& params, const QByteArray& type );
        static QByteArray playlistSortToString(SortingType sorting);
        static QByteArray playlistArtistPickToString(ArtistPick pick);
        static QByteArray dynamicControlToString(DynamicControlItem control);
        static QByteArray dynamicFeedbackToString(DynamicFeedbackParam param);

        QSharedDataPointer<DynamicPlaylistData> d;
    };

    ECHONEST_EXPORT QDebug operator<<(QDebug d, const Echonest::DynamicPlaylist& playlist);


} // namespace


Q_DECLARE_METATYPE( Echonest::DynamicPlaylist )

#endif
