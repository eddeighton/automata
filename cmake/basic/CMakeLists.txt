
cmake_minimum_required(VERSION 3.14.2)

#get boost
include( ${AUTOMATA_ROOT_DIR}/cmake/boost_include.cmake )

set( AUTOMATA_SOURCES
    ${AUTOMATA_SRC_DIR}/automata.hpp
    ${AUTOMATA_SRC_DIR}/automata.cpp
    
    )
    
add_library( automatalib 
                    ${AUTOMATA_SOURCES}
				)

set_target_properties( automatalib PROPERTIES DEBUG_POSTFIX d )

link_boost( automatalib filesystem )
link_boost( automatalib iostreams )
link_boost( automatalib serialization )

install( TARGETS automatalib DESTINATION bin)