find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

find_package(GLFW3 REQUIRED)

# Path to glad directory
set(GLAD_SOURCES_DIR "${CMAKE_SOURCE_DIR}/conan/external/glad")
# Path to glad cmake files
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

# Specify glad settings
set(GLAD_LIBRARY_NAME glad_gl_core_41)
glad_add_library(${GLAD_LIBRARY_NAME} REPRODUCIBLE MX API gl:core=4.1)