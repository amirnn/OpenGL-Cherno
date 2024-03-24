
// #define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

// #define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "GLProgram.hpp"
#include "../ChernoGL/Vertex/Vertex.hpp"

namespace cherno {

static const vertex::Vertex vertices[3] = {{{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
                                           {{0.6f, -0.4f}, {0.f, 1.f, 0.f}},
                                           {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void mat4x4_ortho(Eigen::Matrix4f M, float l, float r, float b, float t,
                         float n, float f) {
  M(0, 0) = 2.f / (r - l);
  M(0, 1) = M(0, 2) = M(0, 3) = 0.f;

  M(1, 1) = 2.f / (t - b);
  M(1, 0) = M(1, 2) = M(1, 3) = 0.f;

  M(2, 2) = -2.f / (f - n);
  M(2, 0) = M(2, 1) = M(2, 3) = 0.f;

  M(3, 0) = -(r + l) / (r - l);
  M(3, 1) = -(t + b) / (t - b);
  M(3, 2) = -(f + n) / (f - n);
  M(3, 3) = 1.f;
}

void GLProgram::Init() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

#if defined(APPLE_SYSTEM)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  auto &window = m_state.window;

  window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version),
         GLAD_VERSION_MINOR(version));

  std::cout << glGetString(GL_VERSION) << std::endl;

  glfwSwapInterval(1);

  // NOTE: OpenGL error checks have been omitted for brevity

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // auto opt = Shader::CreateShaderFromSourceFile("src/Shaders/vertex.shader");
  auto opt = Shader::CreateShaderFromSourceFile("/Users/amirnourinia/Developer/cpp/OpenGL-Cherno/src/Shaders/vertex.shader");

  if ( not opt.has_value())
  {
    std::cout << "Something went wrong!";
  }
  Shader vertexShader = opt.value();
      // Shader::CreateShaderFromSourceFile("src/Shaders/vertex.shader").value();
  Shader fragmentShader =
      Shader::CreateShaderFromSourceFile("/Users/amirnourinia/Developer/cpp/OpenGL-Cherno/src/Shaders/fragment.shader").value();
      // Shader::CreateShaderFromSourceFile("src/Shaders/fragment.shader").value();
      m_state.programPtr = std::make_shared<Program>(std::vector<Shader>{vertexShader, fragmentShader});

  m_state.mvpLocation = glGetUniformLocation(m_state.programPtr->GetId(), "MVP");
  const GLint vpos_location = glGetAttribLocation(m_state.programPtr->GetId(), "vPos");
  const GLint vcol_location = glGetAttribLocation(m_state.programPtr->GetId(), "vCol");

  glGenVertexArrays(1, &m_state.vertexArray);
  glBindVertexArray(m_state.vertexArray);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertex::Vertex),
                        (void *)offsetof(vertex::Vertex, pos));
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertex::Vertex),
                        (void *)offsetof(vertex::Vertex, col));
}

void GLProgram::MainLoop() {
    auto& window = m_state.window;
  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    // mat4x4 m, p, mvp;
    Eigen::Matrix4f m, p, mvp;
    m.setIdentity();
    p.setIdentity();
    mvp.setIdentity();

    const auto t = static_cast<float>(glfwGetTime());
    Eigen::Matrix4f rotation{{cos(t), sin(t), 1.0f, 0.0f},
                             {-sin(t), cos(t), 1.0f, 0.0f},
                             {0.0f, 0.0f, 1.0f, 0.0f},
                             {0.0f, 0.0f, 0.0f, 1.0f}};

    m = rotation * m;

    //        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    //
    mvp = p * m;
    mvp.data();
    //        mat4x4_mul(mvp, p, m);

    glUseProgram(m_state.programPtr->GetId());
    glUniformMatrix4fv(m_state.mvpLocation, 1, GL_FALSE, (const GLfloat *)&mvp);
    glBindVertexArray(m_state.vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void GLProgram::CleanUp() {
  glfwDestroyWindow(m_state.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void GLProgram::Start(int argc, char const *argv[]) {
  Init();
  MainLoop();
  CleanUp();
}

GLProgram::~GLProgram() { CleanUp(); }
} // namespace cherno