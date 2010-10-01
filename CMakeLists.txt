project( libechonest )

include(CPack)

cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII" )

find_package( Qt4 COMPONENTS QtCore QtNetwork QtTest REQUIRED )
set( QT_DONT_USE_QTGUI TRUE )

include( ${QT_USE_FILE} )

set(ECHONEST_LIB_MAJOR_VERSION "0")
set(ECHONEST_LIB_MINOR_VERSION "1")
set(ECHONEST_LIB_PATCH_VERSION "0")

set( ECHONEST_LIB_VERSION_STRING "${ECHONEST_LIB_MAJOR_VERSION}.${ECHONEST_LIB_MINOR_VERSION}.${ECHONEST_LIB_PATCH_VERSION}")

IF (CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS( -Wall -Wundef -Wcast-align -Wchar-subscripts -Wpointer-arith
       -Wwrite-strings -Wpacked -Wformat-security -Wmissing-format-attribute
       -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor -Werror )
    ADD_DEFINITIONS( -fvisibility=hidden )
# to be added:
#       -Wshadow
# FIXME we might want this one back in, but Qt 4.4.3 spits gazillions of warnings with it on Linux-64:
#       -Wconversion
ENDIF (CMAKE_COMPILER_IS_GNUCXX)


option(ECHONEST_BUILD_TESTS "Build all unit tests" ON)

if(ECHONEST_BUILD_TESTS)
  enable_testing()
endif(ECHONEST_BUILD_TESTS)


add_subdirectory( src )
add_subdirectory( tests )

