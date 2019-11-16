
cmake_minimum_required(VERSION 3.14.2)

#get boost
include( ${AUTOMATA_ROOT_DIR}/cmake/boost_include.cmake )

#get automata
include( ${AUTOMATA_ROOT_DIR}/cmake/auto/auto_include.cmake )

set( AUTOMATA_SOURCES
    ${AUTOMATA_SRC_DIR}/main.cpp
    )
    
add_executable( auto 
                    ${AUTOMATA_SOURCES}
				)

set_target_properties( auto PROPERTIES DEBUG_POSTFIX d )

link_boost( auto filesystem )
link_boost( auto iostreams )
link_boost( auto serialization )

link_auto( auto )

install( TARGETS auto DESTINATION bin)