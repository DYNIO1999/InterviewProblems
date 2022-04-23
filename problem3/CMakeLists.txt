cmake_minimum_required(VERSION 3.9)
project(PROBLEM_3)
set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-fdiagnostics-color=always)

include_directories (src/)
file (GLOB_RECURSE PROJECT_HEADERS src/*.hpp
                                   src/*.h)
file (GLOB_RECURSE PROJECT_SOURCES src/*.cpp
                                   src/*.cxx
                                   src/*.cc
                                   src/*.c)

add_definitions (-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries (${PROJECT_NAME})

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})