########### next target ###############
# QTEST_MAIN is using QApplication when QT_GUI_LIB is defined
remove_definitions(-DQT_GUI_LIB)

add_definitions( -DDATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/test_data\" )

remove_definitions( -Werror )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../src)

macro(add_echonest_test _source)
    get_filename_component(_name ${_source} NAME_WE)
#     qt4_automoc(${_name} ${_source})
    set(CMAKE_AUTOMOC ON)
    add_executable(${_name} ${_source})
    target_link_libraries(${_name} echonest ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} ${QTCORE_QTNETWORK_LIBRARY} ${QT_QTXML_LIBRARY} ${QJSON_LIBRARIES} )
    add_test(${_name}-test ${EXECUTABLE_OUTPUT_PATH}/${_name})
    qt5_use_modules(${_name} Network Test)
endmacro(add_echonest_test)

add_echonest_test( ArtistTest.cpp )
add_echonest_test( SongTest.cpp )
add_echonest_test( TrackTest.cpp )
add_echonest_test( PlaylistTest.cpp )
add_echonest_test( CatalogTest.cpp )
