cmake_minimum_required(VERSION 3.13)
project(zalloc_tests C)

set(CMAKE_C_STANDARD 11)

find_package(Threads)
find_package(Check)

add_executable(${PROJECT_NAME} zalloc_zfree.h)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CHECK_INCLUDE_DIR}
        ../src/include
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        main.c
        zalloc_zalloc.h
        zalloc_zsize.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CHECK_LIBRARIES} zalloc pthread)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wno-unused-result
        -Wconversion
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