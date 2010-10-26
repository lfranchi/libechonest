# - Try to find libechonest
#
#  ECHONEST_FOUND - system has libechonest
#  ECHONEST_INCLUDE_DIRS - the libechonest include directories
#  ECHONEST_LIBRARIES - link these to use libechonest
#
# (c) Dominik Schmidt <domme@rautelinux.org>
#

# Dependencies
find_package(Qt4 4.6.0 COMPONENTS QtCore QtNetwork REQUIRED)

# Include dir
find_path(ECHONEST_INCLUDE_DIR
  NAMES echonest/echonest_export.h
  PATHS ${KDE4_INCLUDE_DIR} 
)

# Finally the library itself
find_library(ECHONEST_LIBRARY
  NAMES echonest
  PATHS ${KDE4_LIB_DIR}
)

if(ECHONEST_INCLUDE_DIR AND ECHONEST_LIBRARY)
   set(ECHONEST_FOUND TRUE)
   message(STATUS "Found libechonest: ${ECHONEST_INCLUDE_DIR}, ${ECHONEST_LIBRARY}")
else(ECHONEST_INCLUDE_DIR AND ECHONEST_LIBRARY)
   set(ECHONEST_FOUND FALSE)   
   if (ECHONEST_FIND_REQUIRED)
      message(FATAL_ERROR "Could NOT find required package LibEchonest")
   endif(ECHONEST_FIND_REQUIRED)
endif(ECHONEST_INCLUDE_DIR AND ECHONEST_LIBRARY)

mark_as_advanced(ECHONEST_INCLUDE_DIR ECHONEST_LIBRARY)
