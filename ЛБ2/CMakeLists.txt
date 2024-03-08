cmake_minimum_required(VERSION 3.10)
project(FrogGame)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Ofast")

include_directories(GL)  # Указываем путь к заголовочным файлам freeGlut

add_executable(frog_game main.cpp)

target_link_libraries(frog_game ${OPENGL_LIBRARIES} ${CMAKE_SOURCE_DIR}/freeglut.dll)  # Ссылка на библиотеку freeGlut

# Копирование freeglut.dll в папку сборки
add_custom_command(TARGET frog_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/freeglut.dll"
        $<TARGET_FILE_DIR:frog_game>)