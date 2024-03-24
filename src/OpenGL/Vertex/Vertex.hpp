#pragma once

#include <Eigen/Eigen>

namespace cherno {
namespace vertex {

// using namespace glm;
using namespace Eigen;

using vec2 = Vector2f;
using vec3 = Vector3f;

struct Vertex
{
  Vector2f pos;
  Vector3f col;
};

} // namespace vertex

} // namespace cherno
