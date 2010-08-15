
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( LIBECHONEST_TYPES_SRC
       types/Track.cpp
)

set( LIBECHONEST_TYPES_H
       types/Track.h
)

QT4_WRAP_CPP( ${LIBECHONEST_TYPES_H} )

add_library( echonest SHARED ${LIBECHONEST_TYPES_SRC} )
target_link_libraries( echonest ${QT_QTCORE_LIBRARY} )
