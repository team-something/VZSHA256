# Minimum Cmake version
cmake_minimum_required(VERSION 2.6)

###################################################
# PROJECT Configuration
###################################################
# Project's name
project(VZSHA256)
# Set Folder for storing Binaries
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
# Set Folder for storing Executables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
# Set Folder for storing Libraries
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/libs)
# Add Folder with Header Files
include_directories(${CMAKE_SOURCE_DIR}/include)
# Turn on Optimised debugging for gdb
# set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Add CXXFLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")

#####################################################
# Program Compilation
#####################################################
# Build the library
add_library(sha256 STATIC src/sha256.cpp)
# Build the test program
add_executable(test src/test.cpp)
#Link SHA library
target_link_libraries(test sha256)
