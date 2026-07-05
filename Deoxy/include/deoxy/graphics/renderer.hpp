#pragma once

#include "../utilities/color.hpp"
#include <memory>

namespace Deoxy::Graphics {
    class RendererContext;

    /**
     * @ingroup Graphics
     * @brief High-level rendering interface.
     *
     * The Renderer class manages the graphics context and
     * provides functions for clearing the screen and controlling
     * renderer state.
     */
    class Renderer {
        public:
            /**
             * @brief Constructs a renderer instance.
             */
            Renderer();

            /**
             * @brief Destroys the renderer and its resources.
             */
            ~Renderer();

            /**
             * @brief Initializes the renderer.
             */
            void Init();

            /**
             * @brief Shuts down the renderer and releases its resources.
             */
            void Destroy();

            /**
             * @brief Notifies the renderer that the viewport size has changed.
             * 
             * @param width New viewport width in pixels.
             * @param height New viewport height in pixels.
             */
            void OnResize(uint32_t width, uint32_t height);

            /**
             * @brief Clears the current render target.
             *
             * The screen is cleared using the current clear color.
             */
            void Clear();

            void Draw();

            /**
             * @brief Sets the renderer clear color.
             *
             * @param color New clear color.
             */
            void SetClearColor(const Color& color);

            /**
             * @brief Returns the current clear color.
             */
            Color& GetClearColor() { return m_clearColor; }
            const Color& GetClearColor() const { return m_clearColor; }
        private:
            std::unique_ptr<RendererContext> m_context;

            Color m_clearColor = { 0.1f, 0.1f, 0.13f, 1.0f};
    };
}