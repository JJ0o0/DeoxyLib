#pragma once

#include "../utilities/color.hpp"
#include "opengl/gl_shader.hpp"
#include "opengl/gl_vertex_buffer.hpp"
#include "opengl/gl_index_buffer.hpp"
#include "opengl/gl_vertex_array.hpp"
#include <cstdint>
#include <memory>

namespace Deoxy::Graphics {
    /**
     * @ingroup Graphics
     * @brief Manages the underlying graphics API state.
     *
     * Responsible for initializing, destroying and controlling
     * the low-level OpenGL rendering context.
     */
    class RendererContext {
        public:
            /**
             * @brief Initializes OpenGL graphics context.
             */
            void Init();

            /**
             * @brief Destroy graphics context and releases its resources
             */
            void Destroy();

            /**
             * @brief Clears the current render target.
             * 
             * @param color Clear color used for the operation.
             */
            void Clear(const Color& color);

            void Draw();

            /**
             * @brief Notifies the renderer that the viewport size has changed.
             * 
             * @param width New viewport width in pixels.
             * @param height New viewport height in pixels.
             */
            void OnResize(uint32_t width, uint32_t height);
        private:
            std::unique_ptr<OpenGL::GLShader> m_shader = nullptr;
            std::unique_ptr<OpenGL::GLVertexBuffer> m_vbo = nullptr;
            std::unique_ptr<OpenGL::GLIndexBuffer> m_ebo = nullptr;
            std::unique_ptr<OpenGL::GLVertexArray> m_vao = nullptr;
    };
}