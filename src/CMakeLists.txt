
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/extra/qjson/src )

set( LIBECHONEST_SRC
        Track.cpp
        Song.cpp
        Artist.cpp
        Playlist.cpp
        Config.cpp
        Parsing.cpp
        AudioSummary.cpp
        Util.cpp
        ArtistTypes.cpp
        Generator.cpp
        Catalog.cpp
        CatalogEntry.cpp
)

set( LIBECHONEST_H
        echonest_export.h
        Track.h
        Song.h
        Artist.h
        Playlist.h
        Config.h
        AudioSummary.h
        ArtistTypes.h
        Util.h
        Catalog.h
        CatalogEntry.h
)

QT4_WRAP_CPP( ${LIBECHONEST_H} )

add_definitions( -Werror )

add_library( echonest SHARED ${LIBECHONEST_SRC} )
target_link_libraries( echonest qjson ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )
set_target_properties( echonest PROPERTIES VERSION ${ECHONEST_LIB_VERSION} SOVERSION ${ECHONEST_LIB_VERSION} )
install( TARGETS echonest DESTINATION lib )

install( FILES ${LIBECHONEST_H} DESTINATION  include/echonest COMPONENT Devel )
