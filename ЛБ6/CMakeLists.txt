cmake_minimum_required(VERSION 3.10)
project(LAB)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_library(camera camera.cpp)

add_executable(lab main.cpp)


target_link_libraries(lab camera ${OPENGL_LIBRARIES})
