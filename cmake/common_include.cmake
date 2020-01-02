


cmake_minimum_required(VERSION 3.14.2)

find_path( COMMON_INCLUDE_DIR NAMES include W:/workspace/common_install )

include_directories( ${COMMON_INCLUDE_DIR}/include )
link_directories( ${COMMON_INCLUDE_DIR}/lib )
