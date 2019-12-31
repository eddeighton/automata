

cmake_minimum_required(VERSION 3.14.2)

find_path( GLM_INCLUDE_DIR NAMES glm PATHS ${EG_THIRD_PARTY_DIR}/install/cinder/include/ )

include_directories( ${GLM_INCLUDE_DIR} )