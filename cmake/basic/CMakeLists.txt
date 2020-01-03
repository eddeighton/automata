
cmake_minimum_required(VERSION 3.14.2)

#get boost
include( ${AUTOMATA_ROOT_DIR}/cmake/boost_include.cmake )

#get common
include( ${AUTOMATA_ROOT_DIR}/cmake/common_include.cmake )

set( AUTOMATA_HEADERS
    ${AUTOMATA_SRC_DIR}/alphabet.hpp
    ${AUTOMATA_SRC_DIR}/automata.hpp
    ${AUTOMATA_SRC_DIR}/glm_graph_traits.hpp
    )

set( AUTOMATA_SOURCES
    ${AUTOMATA_SRC_DIR}/automata.cpp
    
    )
    
add_library( automatalib 
                    ${AUTOMATA_HEADERS}
                    ${AUTOMATA_SOURCES}
				)

set_target_properties( automatalib PROPERTIES DEBUG_POSTFIX d )

link_boost( automatalib GRAPH )
link_boost( automatalib REGEX )
link_boost( automatalib FILESYSTEM )
link_boost( automatalib IOSTREAMS )
link_boost( automatalib SERIALIZATION )

target_link_libraries( automatalib debug commonlibd.lib optimized commonlib.lib )

install( FILES ${AUTOMATA_HEADERS} DESTINATION include/automata )
install( FILES ${AUTOMATA_ROOT_DIR}/.eg DESTINATION . )
install( TARGETS automatalib DESTINATION lib)