# SRC

add_executable(cherno
    ${CMAKE_SOURCE_DIR}/src/GLProgram/GLProgram.cpp
    ${CMAKE_SOURCE_DIR}/src/ChernoGL/Program/Program.cpp
    ${CMAKE_SOURCE_DIR}/src/ChernoGL/Shader/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils/GLCall.cpp
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