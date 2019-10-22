cmake_minimum_required(VERSION 3.13)
project(zalloc_tests C)

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
        zalloc_zalloc.h
        zalloc_zsize.h
        zalloc_zfree.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CHECK_LIBRARIES} zalloc pthread)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wno-unused-result
        -Wno-unused-variable
        -Wno-sign-conversion
        -Wno-nonnull
)