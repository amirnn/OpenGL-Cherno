# TOP
cmake_minimum_required(VERSION 3.26.0)
project(opengl-cherno LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include("conan/Dependencies.cmake")
add_subdirectory("src")
message(STATUS "Here are:" ${CC} " and, " ${CXX})


# For debugging
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()