#include <deoxy/graphics/opengl/gl_vertex_buffer.hpp>
#include <glad/gl.h>

namespace Deoxy::Graphics::OpenGL {
    GLVertexBuffer::GLVertexBuffer(const std::vector<Vertex>& vertices)
        : m_vertexCount((vertices.size() * sizeof(Vertex)) / sizeof(Vertex)) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    GLVertexBuffer::~GLVertexBuffer() { Destroy(); }

    void GLVertexBuffer::Destroy() {
        if (m_id) {
            glDeleteBuffers(1, &m_id);
            m_id = 0;
        }
    }

    void GLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
    void GLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
}