cmake_minimum_required(VERSION 3.13)
project(zalloc_meta C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN true)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_compile_options(
        # Portability
        -fpie
        -pie
        -fPIC
        -shared

        # Various hardening options
        -fasynchronous-unwind-tables
        -fstack-protector-all
        -fstack-protector-strong

        # Compile-time optimizations
        -pipe
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            -Wall
            -Werror
            -Wextra
            -Wpedantic
            -Wlogical-op
            -Wdouble-promotion
            -Wformat=2
            -Wshadow
            -Wcast-qual
            -Wdisabled-optimization
            -Winit-self
            -Wmissing-include-dirs
            -Wredundant-decls
            -Wstrict-overflow=5
            -Wundef
            -Wconversion
            -Wswitch
            -Winvalid-pch
            -Wformat-nonliteral
            -Wmissing-format-attribute
            -Wno-nonnull-compare
            -fno-delete-null-pointer-checks
    )

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