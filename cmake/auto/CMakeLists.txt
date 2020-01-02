
cmake_minimum_required(VERSION 3.14.2)

#get common
include( ${AUTOMATA_ROOT_DIR}/cmake/common_include.cmake )

#get boost
include( ${AUTOMATA_ROOT_DIR}/cmake/boost_include.cmake )

#get automata
include( ${AUTOMATA_ROOT_DIR}/cmake/auto/auto_include.cmake )

set( AUTOMATA_SOURCES
    ${AUTOMATA_SRC_DIR}/main.cpp
    ${AUTOMATA_SRC_DIR}/command_generate.cpp
    )
    
add_executable( auto 
                    ${AUTOMATA_SOURCES}
				)

set_target_properties( auto PROPERTIES DEBUG_POSTFIX d )

target_link_libraries( auto commonlib.lib )

link_boost( auto filesystem )
link_boost( auto iostreams )
link_boost( auto serialization )

link_auto( auto )

install( TARGETS auto DESTINATION bin)
