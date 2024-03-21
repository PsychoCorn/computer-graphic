cmake_minimum_required(VERSION 3.10)
project(FrogGame)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Ofast")

add_executable(frog_game main.cpp)

target_link_libraries(frog_game ${OPENGL_LIBRARIES})
