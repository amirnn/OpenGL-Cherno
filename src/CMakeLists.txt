# SRC

add_executable(cherno 
    ${CMAKE_SOURCE_DIR}/src/cherno.cpp 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    )

target_link_libraries(
    cherno
    glm::glm
    Eigen3::Eigen
    glfw
    ${GLAD_LIBRARY_NAME}
)

# install(TARGETS opengl-cherno DESTINATION "."
#         RUNTIME DESTINATION bin
#         ARCHIVE DESTINATION lib
#         LIBRARY DESTINATION lib
#         )