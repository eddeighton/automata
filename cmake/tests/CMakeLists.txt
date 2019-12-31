
cmake_minimum_required(VERSION 3.14.2)

#get boost
include( ${AUTOMATA_ROOT_DIR}/cmake/boost_include.cmake )

#get gtest
include( ${AUTOMATA_ROOT_DIR}/cmake/gtest_include.cmake )

#get automata
include( ${AUTOMATA_ROOT_DIR}/cmake/auto/auto_include.cmake )

set( AUTOMATA_TEST_DIR ${AUTOMATA_ROOT_DIR}/tests )
    
file( GLOB AUTOMATA_TEST_SOURCES ${AUTOMATA_TEST_DIR}/*.cpp )
#foreach( F ${DATABASE_TEST_SOURCES})
#    message( STATUS "Found unit test: " ${F} )
#endforeach( F )
source_group( automata/tests FILES ${AUTOMATA_TEST_SOURCES} )

add_executable( automata_tests
					${AUTOMATA_TEST_SOURCES}
				)
                
set_target_properties( automata_tests PROPERTIES DEBUG_POSTFIX d )

link_boost( automata_tests filesystem )
link_boost( automata_tests iostreams )
link_boost( automata_tests serialization )

link_gtest( automata_tests )
link_gtest_main( automata_tests )

link_auto( auto )

install( TARGETS automata_tests DESTINATION bin)
