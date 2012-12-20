
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
)

QT5_WRAP_CPP( ${LIBECHONEST_H} )

SET( OS_SPECIFIC_LINK_LIBRARIES "" )
IF( APPLE OR MINGW )
  SET( OS_SPECIFIC_LINK_LIBRARIES ${QJSON_LIBRARIES} )
ELSE( APPLE OR MINGW )
  SET( OS_SPECIFIC_LINK_LIBRARIES ${QJSON_LDFLAGS} )
ENDIF( APPLE OR MINGW )


add_library( echonest SHARED ${LIBECHONEST_SRC} )
target_link_libraries( echonest ${OS_SPECIFIC_LINK_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )
set_target_properties( echonest PROPERTIES VERSION ${ECHONEST_LIB_VERSION} SOVERSION ${ECHONEST_LIB_VERSION_SONAME} )
qt5_use_modules( echonest Core Network Xml )
install( TARGETS echonest   RUNTIME DESTINATION bin
                            LIBRARY DESTINATION lib${LIB_SUFFIX}
                            ARCHIVE DESTINATION lib${LIB_SUFFIX}
)

install( FILES ${LIBECHONEST_H} DESTINATION  include/echonest COMPONENT Devel )
