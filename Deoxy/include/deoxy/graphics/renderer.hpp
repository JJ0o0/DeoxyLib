#pragma once

#include "../utilities/color.hpp"
#include <memory>
namespace Deoxy::Graphics {
    class RendererContext;

    class Renderer {
        public:
            Renderer();
            ~Renderer();

            void Init();
            void Destroy();

            void OnResize(uint32_t width, uint32_t height);

            void Clear();
            void SetClearColor(const Color& color);
        private:
            std::unique_ptr<RendererContext> m_context;

            Color m_clearColor = { 0.1f, 0.1f, 0.13f, 1.0f};
    };
}