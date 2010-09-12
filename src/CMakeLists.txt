
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( LIBECHONEST_TYPES_SRC
        Track.cpp
        Song.cpp
        Artist.cpp
        Playlist.cpp
        Config.cpp
        Parsing.cpp
)

set( LIBECHONEST_TYPES_H
        Track.h
        Song.h
        Artist.h
        Playlist.h
        Config.h
)

QT4_WRAP_CPP( ${LIBECHONEST_TYPES_H} )

add_library( echonest SHARED ${LIBECHONEST_TYPES_SRC} )
target_link_libraries( echonest ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )
