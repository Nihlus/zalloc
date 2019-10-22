cmake_minimum_required(VERSION 3.13)
project(zalloc C)

set(ZALLOC_VERSION_MAJOR 1)
set(ZALLOC_VERSION_MINOR 0)
set(ZALLOC_VERSION_PATCH 0)
set(ZALLOC_VERSION_STRING ${ZALLOC_VERSION_MAJOR}.${ZALLOC_VERSION_MINOR}.${ZALLOC_VERSION_PATCH})

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

target_include_directories(${PROJECT_NAME}
    PRIVATE
        internal
    PUBLIC
        $<INSTALL_INTERFACE:include/zalloc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/zalloc>
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        VERSION ${ZALLOC_VERSION_STRING}
        SOVERSION ${ZALLOC_VERSION_STRING}
)