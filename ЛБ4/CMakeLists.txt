cmake_minimum_required(VERSION 3.10)
project(FrogGame)

find_package(OpenGL REQUIRED)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Ofast -Os")

add_executable(frog_game main.c)

file(COPY ${CMAKE_SOURCE_DIR}/lib/primitives/sprites DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(frog_game ${OPENGL_LIBRARIES})
