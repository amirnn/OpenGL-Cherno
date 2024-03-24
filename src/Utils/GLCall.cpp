#include <iostream>

#include "GLCall.hpp"

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall()
{
  while (uint error = glGetError())
  {
    std::cout << "[OpenGL Error] : (" << error << ")" << std::endl;
    if (error == GL_NO_ERROR)
    {
      return false;
    }
  }
  return true;
}