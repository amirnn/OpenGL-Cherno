#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define OPENGL_CHERNO_EXPORT __declspec(dllexport)
#else
  #define OPENGL_CHERNO_EXPORT
#endif

OPENGL_CHERNO_EXPORT void opengl_cherno();
OPENGL_CHERNO_EXPORT void opengl_cherno_print_vector(const std::vector<std::string> &strings);
