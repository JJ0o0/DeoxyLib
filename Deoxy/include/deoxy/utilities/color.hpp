#pragma once

#include "deoxy/utilities/math.hpp"
#include <glm/glm.hpp>

namespace Deoxy {
    /**
     * @ingroup Utilities
     * @brief RGBA color using normalized floating-point components.
     *
     * Each component is in the range [0.0, 1.0].
     */
    using Color = glm::vec4;

    /**
     * @ingroup Utilities
     * @brief RGBA color using 8-bit integer components.
     *
     * Each component is in the range [0, 255].
     */
    using Color32 = glm::u8vec4;

    /**
     * @ingroup Utilities
     * @brief Converts an RGBA8 color to a normalized floating-point color.
     *
     * @param color32 Source color.
     * @return Equivalent color in the range [0.0, 1.0].
     */
    inline Color ToNormalizedColor(const Color32& color32) {
        return Color{
            color32.r / 255.0f,
            color32.g / 255.0f,
            color32.b / 255.0f,
            color32.a / 255.0f
        };
    };

    /**
     * @ingroup Utilities
     * @brief Converts a normalized floating-point color to RGBA8 format.
     *
     * @param color Source color.
     * @return Equivalent color in the range [0, 255].
     */
    inline Color32 ToColor32(const Color& color) {
        return Color32{
            static_cast<uint8_t>(Math::Round(color.r * 255.0f)),
            static_cast<uint8_t>(Math::Round(color.g * 255.0f)),
            static_cast<uint8_t>(Math::Round(color.b * 255.0f)),
            static_cast<uint8_t>(Math::Round(color.a * 255.0f))
        };
    }
};