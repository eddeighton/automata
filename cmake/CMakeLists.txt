
cmake_minimum_required(VERSION 3.14.2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_path( EG_THIRD_PARTY_DIR NAMES install PATHS ${CMAKE_PARENT_PATH} )

set( CMAKE_PARENT_PATH ${CMAKE_CURRENT_LIST_DIR}/.. )
find_path( AUTOMATA_ROOT_DIR NAMES src PATHS ${CMAKE_PARENT_PATH} )

######################################
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)
#set(CMAKE_INSTALL_PREFIX ${AUTOMATA_ROOT_DIR} CACHE STRING INTERNAL FORCE)

set( AUTOMATA_SRC_DIR ${AUTOMATA_ROOT_DIR}/src )

include_directories( ${AUTOMATA_SRC_DIR} )
include_directories( ${AUTOMATA_ROOT_DIR} )
link_directories( ${PROJECT_DIR}/bin )

set( CMAKE_CXX_STANDARD 17 )

######################################
#win32 specific settings
IF( ${WIN32} )

# /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MP
#set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /MP")

add_compile_options(/std:c++17)
#add_compile_options(/Zc:__cplusplus)
add_compile_options(/DWIN32)
add_compile_options(/D_WINDOWS)
add_compile_options(/MP)
add_compile_options(/W3)

add_definitions(-D_WIN32_WINNT=0x0601)
add_definitions(-DNOMINMAX -D_NOMINMAX)
#add_definitions(-DUNICODE -D_UNICODE)
##specify the character set to use for all projects
add_definitions(-DSBCS -D_SBCS)

##ensure c++ dependencies are installed
include (InstallRequiredSystemLibraries)

ENDIF( ${WIN32} )

project( automata )

add_subdirectory( basic )
add_subdirectory( auto )
add_subdirectory( tests )