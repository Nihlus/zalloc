cmake_minimum_required(VERSION 3.13)
project(zalloc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN true)

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
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
        -Wno-nonnull-compare
        -fno-delete-null-pointer-checks
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
            gcov
    )

    target_compile_options(
            ${PROJECT_NAME}
            PRIVATE
            --coverage
            -fprofile-arcs
            -ftest-coverage
    )

    target_link_options(
            ${PROJECT_NAME}
            PRIVATE
            --coverage
            -fprofile-arcs
            -ftest-coverage
    )
endif()