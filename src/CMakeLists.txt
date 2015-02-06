
include_directories( ${QJSON_INCLUDE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR} )

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
        CatalogUpdateEntry.cpp
        CatalogSong.cpp
        CatalogArtist.cpp
        CatalogItem.cpp
        TypeInformation.cpp
        Genre.cpp
        qjsonwrapper/Json.cpp
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
        CatalogUpdateEntry.h
        CatalogSong.h
        CatalogArtist.h
        CatalogItem.h
        TypeInformation.h
        Genre.h
        CommonTypes.h
)

QT_WRAP_CPP( ${LIBECHONEST_H} )

add_library( ${ECHONEST_LIB_TARGET_NAME} SHARED ${LIBECHONEST_SRC} )
target_link_libraries( ${ECHONEST_LIB_TARGET_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QJSON_LIBRARIES} )
set_target_properties( ${ECHONEST_LIB_TARGET_NAME} PROPERTIES VERSION ${ECHONEST_LIB_VERSION} SOVERSION ${ECHONEST_LIB_VERSION_SONAME} )
qt5_use_modules( ${ECHONEST_LIB_TARGET_NAME} Core Network Xml )
install( TARGETS ${ECHONEST_LIB_TARGET_NAME}   RUNTIME DESTINATION bin
                            LIBRARY DESTINATION lib${LIB_SUFFIX}
                            ARCHIVE DESTINATION lib${LIB_SUFFIX}
)

install( FILES ${LIBECHONEST_H} DESTINATION  include/echonest${ECHONEST_LIB_VERSION_SUFFIX} COMPONENT Devel )
