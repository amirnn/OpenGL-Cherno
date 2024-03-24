#pragma once

#include <sys/types.h>
#include <glad/gl.h>

#if defined(WIN32)
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#include <csignal>
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#endif

#define GLCall(x) GLClearError(); \
  x;                              \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(char const* function, char const* file, int line);