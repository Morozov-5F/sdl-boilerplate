cmake_minimum_required(VERSION 3.17)
project(sdl_boilerplate C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(sdl/libsdl)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_executable(sdl_boilerplate main.c)

target_link_libraries(sdl_boilerplate SDL2-static)