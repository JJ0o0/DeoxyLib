#include <deoxy/graphics/opengl/gl_vertex_array.hpp>
#include <deoxy/graphics/vertex.hpp>
#include <glad/gl.h>

namespace Deoxy::Graphics::OpenGL {
    GLVertexArray::GLVertexArray() {
        glGenVertexArrays(1, &m_id);
    }

    GLVertexArray::~GLVertexArray() { Destroy(); }

    void GLVertexArray::Destroy() {
        if (m_id) {
            glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }
    }

    void GLVertexArray::Bind() const { glBindVertexArray(m_id); }
    void GLVertexArray::Unbind() const { glBindVertexArray(0); }

    void GLVertexArray::AddVertexBuffer(GLVertexBuffer& vbo) {
        Bind();
        vbo.Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void GLVertexArray::AddIndexBuffer(GLIndexBuffer& ebo) {
        Bind();
        ebo.Bind();
    }
}