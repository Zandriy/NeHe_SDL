cmake_minimum_required (VERSION 2.6)
project (NeHe)

# Compile Debug version
SET(CMAKE_CXX_FLAGS "-g")

# The version number.
set (NeHe_VERSION_MAJOR 1)
set (NeHe_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/NeHeConfig.h.in"
	"${PROJECT_BINARY_DIR}/NeHeConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find NeHe_Config.h
include_directories("${PROJECT_BINARY_DIR}")

 add_subdirectory (src) 
 
