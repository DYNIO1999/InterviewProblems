cmake_minimum_required(VERSION 3.9)
project(PROBLEM_2)
set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-fdiagnostics-color=always)

option (GLFW_INSTALL OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (vendor/glfw)

include_directories (src/
                     vendor/glad/include/
                     vendor/glfw/include/
                     vendor/glm/include/glm
                     )
file (GLOB         GLAD_SOURCES vendor/glad/src/glad.c)
file (GLOB_RECURSE PROJECT_HEADERS src/*.hpp
                                   src/*.h)
file (GLOB_RECURSE PROJECT_SOURCES src/*.cpp
                                   src/*.cxx
                                   src/*.cc
                                   src/*.c)

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${GLAD_SOURCES})
target_link_libraries (${PROJECT_NAME}
                       glfw
                       ${GLFW_LIBRARIES}
                       ${GLAD_LIBRARIES})

set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})