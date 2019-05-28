cmake_minimum_required(VERSION 3.13)
project(zalloc_meta C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(src)
add_subdirectory(tests)