#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

namespace Deoxy::Math {
    /**
     * @ingroup Utilities
     * @brief Two-dimensional vector type.
     */
    using Vector2 = glm::vec2;

    /**
     * @ingroup Utilities
     * @brief Three-dimensional vector type.
     */
    using Vector3 = glm::vec3;

    /**
     * @ingroup Utilities
     * @brief Four-dimensional vector type.
     */
    using Vector4 = glm::vec4;

    /**
     * @ingroup Utilities
     * @brief 4x4 matrix type.
     */
    using Matrix4x4 = glm::mat4;
    
    /**
     * @ingroup Utilities
     * @brief Computes the sine of an angle in radians.
     *
     * @param x Angle in radians.
     * @return Sine of the angle.
     */
    inline float Sin(float x) { return std::sin(x); }

    /**
     * @ingroup Utilities
     * @brief Rounds a floating-point value to the nearest integer.
     *
     * @param x Value to round.
     * @return Rounded integer value.
     */
    inline int Round(float x) { return std::round(x); }

    /**
     * @ingroup Utilities
     * @brief Returns a pointer to the first component of a GLM vector.
     *
     * Useful when interfacing with APIs such as Dear ImGui and OpenGL
     * that expect contiguous float arrays.
     *
     * @param value Vector to access.
     * @return Pointer to the first component.
     */
    template<typename T>
    inline float* GetPointer(T& value) {
        return glm::value_ptr(value);
    }
}