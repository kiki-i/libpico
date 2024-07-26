cmake_minimum_required(VERSION 3.10)
project(libpico)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")

set(PICO_SOURCE_DIR "${CMAKE_SOURCE_DIR}/rxs_parsing_core")
include_directories("${PICO_SOURCE_DIR}/preprocess")

file(GLOB PICO_SOURCE
  "${CMAKE_SOURCE_DIR}/src/*.cxx"
  "${PICO_SOURCE_DIR}/*.cxx"
  "${PICO_SOURCE_DIR}/preprocess/generated/*.cpp")

add_library(libpico SHARED ${PICO_SOURCE})
set_target_properties(libpico PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(libpico PROPERTIES LINK_FLAGS "${CMAKE_SOURCE_DIR}/exports.def")
else()
  set_target_properties(libpico PROPERTIES LINK_FLAGS "${CMAKE_SOURCE_DIR}/exports.ld")
endif()

target_compile_options(libpico PRIVATE -include "${PROJECT_SOURCE_DIR}/uglyFix.hxx")
