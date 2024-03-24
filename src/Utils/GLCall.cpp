#include <iostream>

#include "GLCall.hpp"

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(char const* function, char const* file, int line)
{
  while (uint error = glGetError())
  {
    std::cout << "[OpenGL Error] : (" << error << "), " << function << \
        file << "line: " << line << std::endl;
    if (error == GL_NO_ERROR)
    {
      return false;
    }
  }
  return true;
}