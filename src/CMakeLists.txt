# SRC

add_executable(opengl-cherno 
    ${CMAKE_SOURCE_DIR}/src/opengl-cherno.cpp 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    )

# install(TARGETS opengl-cherno DESTINATION "."
#         RUNTIME DESTINATION bin
#         ARCHIVE DESTINATION lib
#         LIBRARY DESTINATION lib
#         )