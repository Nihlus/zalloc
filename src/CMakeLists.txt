cmake_minimum_required(VERSION 3.13)
project(zalloc C)

add_library(${PROJECT_NAME} SHARED)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        zalloc.c
        internal/zmem_header.h
        internal/zmem_header.c
        internal/helpers.h
        internal/helpers.c
        include/zalloc/za_attributes.h
    PUBLIC
        include/zalloc/zalloc.h
)

target_include_directories(${PROJECT_NAME} PRIVATE include/zalloc internal)