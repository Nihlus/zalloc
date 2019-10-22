cmake_minimum_required(VERSION 3.13)
project(zalloc_meta C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN true)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_compile_options(
        -Wall
        -Wextra
        -Wconversion
        -pedantic
        -Werror
        -Wno-nonnull-compare
        -fno-delete-null-pointer-checks
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_libraries(
        gcov
    )

    add_compile_options(
        --coverage
        -fprofile-arcs
        -ftest-coverage
    )

    add_link_options(
        --coverage
        -fprofile-arcs
        -ftest-coverage
    )
endif()

add_subdirectory(src)
add_subdirectory(tests)