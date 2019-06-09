cmake_minimum_required(VERSION 3.13)
project(zalloc_tests C)

set(CMAKE_C_STANDARD 11)

find_package(Threads)
find_package(Check)

add_executable(${PROJECT_NAME})

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
        base.h
        zalloc_size.h
)

target_link_libraries(${PROJECT_NAME} ${CHECK_LIBRARIES} zalloc pthread)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wno-unused-result
        -Wconversion
)