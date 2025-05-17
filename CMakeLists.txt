cmake_minimum_required(VERSION 3.10)
project(libpico)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -funroll-loops -DNDEBUG")

set(PICO_SOURCE_DIR "${CMAKE_SOURCE_DIR}/rxs_parsing_core")
include_directories("${PICO_SOURCE_DIR}/preprocess")

file(GLOB PICO_SOURCE
  "${CMAKE_SOURCE_DIR}/src/*.cxx"
  "${PICO_SOURCE_DIR}/*.cxx"
  "${PICO_SOURCE_DIR}/preprocess/generated/*.cpp")

add_library(libpico SHARED ${PICO_SOURCE})
set_target_properties(libpico PROPERTIES PREFIX "")

if(NOT WIN32)
  set(CMAKE_C_VISIBILITY_PRESET hidden)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
endif()

target_compile_options(libpico PRIVATE -include "${PROJECT_SOURCE_DIR}/src/compatiblePatch.hxx")

string(REPLACE "-nostartfiles" "" CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY}")
string(REPLACE "-nostdlib"     "" CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY}")
string(REPLACE "-nostartfiles" "" CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
string(REPLACE "-nostdlib"     "" CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
