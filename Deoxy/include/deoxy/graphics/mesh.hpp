#pragma once

#include "opengl/gl_vertex_buffer.hpp"
#include "opengl/gl_index_buffer.hpp"
#include "opengl/gl_vertex_array.hpp"
#include "vertex.hpp"
#include <memory>

namespace Deoxy::Graphics {
    class Mesh {
        public:
            Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
            ~Mesh() { Destroy(); }

            void Draw() const;
            void Destroy();

        private:
            std::unique_ptr<OpenGL::GLVertexBuffer> m_vbo;
            std::unique_ptr<OpenGL::GLIndexBuffer> m_ebo;
            std::unique_ptr<OpenGL::GLVertexArray> m_vao;
    };
}