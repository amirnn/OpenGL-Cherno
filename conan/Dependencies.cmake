# find_package(Boost REQUIRED COMPONENTS system)
# include_directories(${Boost_INCLUDE_DIRS})

find_package(GLFW3 REQUIRED)
include_directories(${glfw3_INCLUDE_DIRS})

# Path to glad directory
set(GLAD_SOURCES_DIR "${CMAKE_SOURCE_DIR}/conan/external/glad")
# Path to glad cmake files
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
include_directories()

find_package(glm REQUIRED)
include_directories(${glm_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${Eigen3_INCLUDE_DIRS})

# Specify glad settings
# Look at GladConfig.cmake file for better understanding
if(APPLE)
    set(GLAD_LIBRARY_NAME glad_gl_core_41)
    glad_add_library(${GLAD_LIBRARY_NAME} REPRODUCIBLE API gl:core=4.1)
elseif(WIN32)
    set(GLAD_LIBRARY_NAME glad_gl_core_46)
    glad_add_library(${GLAD_LIBRARY_NAME} API gl:core=4.6)
#    glad_add_library(${GLAD_LIBRARY_NAME} MX API gl:core=4.1)
endif(APPLE)

