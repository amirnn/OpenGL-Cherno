# find_package(Boost REQUIRED COMPONENTS system)
# include_directories(${Boost_INCLUDE_DIRS})

find_package(GLFW3 REQUIRED)
include_directories(${glfw3_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${glm_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${Eigen3_INCLUDE_DIRS})

if(BUILD_GLAD_FROM_SOURCES)
    # Path to glad directory
    set(GLAD_SOURCES_DIR "${CMAKE_SOURCE_DIR}/conan/external/glad")
    # Path to glad cmake files
    add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

    # Specify glad settings
    # Look at GladConfig.cmake file for better understanding
    if(APPLE)
        set(GLAD_LIBRARY_NAME glad_gl_core_41)
        glad_add_library(${GLAD_LIBRARY_NAME} API gl:core=4.1)
        add_compile_definitions(APPLE_SYSTEM)
    elseif(WIN32)
        set(GLAD_LIBRARY_NAME glad_gl_core_46)
        glad_add_library(${GLAD_LIBRARY_NAME} API gl:core=4.6)
    endif()
else()
    if(APPLE)
        set(GLAD_SRC "${CMAKE_SOURCE_DIR}/conan/external/glad-generated/ogl-core-41-all-extensions-alias/src/gl.c")
        set(GLAD_INCLUDE "${CMAKE_SOURCE_DIR}/conan/external/glad-generated/ogl-core-41-all-extensions-alias/include")
        add_compile_definitions(APPLE_SYSTEM)
    elseif(WIN32)
        set(GLAD_SRC "${CMAKE_SOURCE_DIR}/conan/external/glad-generated/ogl-core-46-all-extensions-alias/src/gl.c")
        set(GLAD_INCLUDE "${CMAKE_SOURCE_DIR}/conan/external/glad-generated/ogl-core-46-all-extensions-alias/include")
    endif()
    set(GLAD_LIBRARY_NAME glad_gl_core_all_extensions_alias)
    add_library(${GLAD_LIBRARY_NAME} STATIC ${GLAD_SRC})
    include_directories(${GLAD_INCLUDE})
endif()




