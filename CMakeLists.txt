cmake_minimum_required(VERSION 3.15)
project(opengl-cherno CXX)



set(CMAKE_CXX_STANDARD 23)
# TOP
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include("conan/Dependencies.cmake")
add_subdirectory("src")
message(STATUS "Here are:" ${CC} " and, " ${CXX})