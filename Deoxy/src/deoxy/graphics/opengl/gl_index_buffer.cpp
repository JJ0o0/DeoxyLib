#include <deoxy/graphics/opengl/gl_index_buffer.hpp>

#include <glad/gl.h>

namespace Deoxy::Graphics::OpenGL {
    GLIndexBuffer::GLIndexBuffer(const std::vector<uint32_t>& indices)
        : m_indexCount(indices.size()) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    }

    GLIndexBuffer::~GLIndexBuffer() { Destroy(); }

    void GLIndexBuffer::Destroy() {
        if (m_id) {
            glDeleteBuffers(1, &m_id);
            m_id = 0;
        }
    }

    void GLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
    void GLIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}