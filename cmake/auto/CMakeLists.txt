
cmake_minimum_required(VERSION 3.14.2)

#get common
include( ${AUTOMATA_ROOT_DIR}/cmake/common_include.cmake )

#get boost
include( ${AUTOMATA_ROOT_DIR}/cmake/boost_include.cmake )

#get glm
include( ${AUTOMATA_ROOT_DIR}/cmake/glm_include.cmake )

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

link_boost( auto GRAPH )
link_boost( auto REGEX )
link_boost( auto FILESYSTEM )
link_boost( auto IOSTREAMS )
link_boost( auto SERIALIZATION )

target_link_libraries( auto debug commonlibd.lib optimized commonlib.lib )

link_auto( auto )

install( TARGETS auto DESTINATION bin)
