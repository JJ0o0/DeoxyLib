#pragma once

#include "gl_vertex_buffer.hpp"
#include "gl_index_buffer.hpp"
#include <cstdint>

namespace Deoxy::Graphics::OpenGL {
    class GLVertexArray {
        public:
            GLVertexArray();
            ~GLVertexArray();

            void Destroy();
            void Bind() const;
            void Unbind() const;

            void AddVertexBuffer(GLVertexBuffer& vbo);
            void AddIndexBuffer(GLIndexBuffer& ebo);
        private:
            uint32_t m_id = 0;
    };
}