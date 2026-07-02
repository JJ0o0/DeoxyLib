#pragma once

#include "../utilities/color.hpp"
#include <cstdint>

namespace Deoxy::Graphics {
    class RendererContext {
        public:
            void Init();
            void Destroy();

            void Clear(Color& color);
            void OnResize(uint32_t width, uint32_t height);
    };
}