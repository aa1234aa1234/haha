cmake_minimum_required(VERSION 3.31)
project(project)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/editor/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp"
)
message(${SOURCES})
add_executable(project ${SOURCES} Thirdparty/src/gl.c)

add_subdirectory(Thirdparty/glfw)
include_directories(Thirdparty/includes)
include_directories(editor)
include_directories(ui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(project glfw opengl32)
