# This file and all other CMakeLists.txt files in this project are
# copyright Leo Franchi, 2010, and licensed under the MIT license.

project( libechonest )

cmake_minimum_required( VERSION 2.6 )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII" )

# find_package( Qt4 COMPONENTS QtCore QtNetwork QtTest REQUIRED )
# include( ${QT_USE_FILE} )
find_package(Qt5Core REQUIRED)


find_package(QJSON REQUIRED)

set( ECHONEST_LIB_MAJOR_VERSION "2" )
set( ECHONEST_LIB_MINOR_VERSION "1" )
set( ECHONEST_LIB_PATCH_VERSION "0" )
set( ECHONEST_LIB_VERSION "${ECHONEST_LIB_MAJOR_VERSION}.${ECHONEST_LIB_MINOR_VERSION}.${ECHONEST_LIB_PATCH_VERSION}" )

set( ECHONEST_LIB_VERSION_SONAME "${ECHONEST_LIB_MAJOR_VERSION}.${ECHONEST_LIB_MINOR_VERSION}")

if (CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS( -Wall -Wundef -Wcast-align -Wchar-subscripts -Wpointer-arith
       -Wwrite-strings -Wpacked -Wformat-security -Wmissing-format-attribute
       -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor )
    if ( NOT WIN32 )
        add_definitions( -fvisibility=hidden )
    endif()

# to be added:
#       -Wshadow
# FIXME we might want this one back in, but Qt 4.4.3 spits gazillions of warnings with it on Linux-64:
#       -Wconversion
endif(CMAKE_COMPILER_IS_GNUCXX)
if(MSVC)
    # since msvc doesn't implement it, we can simply ignore the warning:
    # cf. http://msdn.microsoft.com/en-us/library/sa28fef8.aspx
    add_definitions(/wd4290)
endif(MSVC)


option(ECHONEST_BUILD_TESTS "Build all unit tests" ON)

if(ECHONEST_BUILD_TESTS)
  enable_testing()
endif(ECHONEST_BUILD_TESTS)

set( CPACK_GENERATOR "TBZ2" "DEB" )
set( CPACK_PACKAGE_VERSION_MAJOR "${ECHONEST_LIB_MAJOR_VERSION}" )
set( CPACK_PACKAGE_VERSION_MINOR "${ECHONEST_LIB_MINOR_VERSION}" )
set( CPACK_PACKAGE_VERSION_PATCH "${ECHONEST_LIB_PATCH_VERSION}" )
set( CPACK_PACKAGE_VERSION "${ECHONEST_LIB_VERSION}" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "lfranchi@kde.org" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "A c++/qt library to access the APIs provided by The Echo Nest." )

if( APPLE )
    set( CPACK_GENERATOR "DragNDrop" )
    set( CPACK_DMG_FORMAT "UDBZ" )
    set( CPACK_DMG_VOLUME_NAME "libechonest" )
    set( CPACK_SYSTEM_NAME "OSX" )
endif( APPLE )

# pkg-config
#add extra search paths for libraries and includes
SET (LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
SET (LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where lib will install")
SET (INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")
IF (NOT WIN32)
  CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/libechonest.pc.in
                  ${CMAKE_CURRENT_BINARY_DIR}/libechonest.pc
                  @ONLY)
  INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/libechonest.pc
           DESTINATION lib${LIB_SUFFIX}/pkgconfig)
ENDIF (NOT WIN32)

include(CPack)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                         COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

# make uninstall support
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

add_subdirectory( src )

if( ECHONEST_BUILD_TESTS )
    add_subdirectory( tests )
endif( ECHONEST_BUILD_TESTS )

