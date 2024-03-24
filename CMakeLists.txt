# TOP
cmake_minimum_required(VERSION 3.26.0)
project(opengl-cherno LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# https://cmake.org/cmake/help/latest/module/FindPython3.html#hints
# https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html#variable:CMAKE_FIND_FRAMEWORK
# We find the python so glad does not choose its own.
# Unfortunatly, we have to add it ourselves into GladConfig. Python3 is important.
# if(APPLE)
#     set(Python3_FIND_FRAMEWORK LAST)
#     find_package(Python3 COMPONENTS Interpreter REQUIRED)
# endif(APPLE)

set(BUILD_GLAD_FROM_SOURCES OFF)

include("conan/Dependencies.cmake")
add_subdirectory("src")
message(STATUS "Here are:" ${CC} " and, " ${CXX})


# For debugging
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()