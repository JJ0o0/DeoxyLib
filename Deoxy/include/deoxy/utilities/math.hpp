#pragma once

#include <glm/glm.hpp>
#include <cmath>

namespace Deoxy::Math {
    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;
    using Matrix4x4 = glm::mat4;
    
    inline float Sin(float x) { return std::sin(x); }
    inline int Round(float x) { return std::round(x); }
}