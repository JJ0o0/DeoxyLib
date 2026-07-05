#include <deoxy/graphics/mesh.hpp>
#include <glad/gl.h>

namespace Deoxy::Graphics {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        m_vao = std::make_unique<OpenGL::GLVertexArray>();
        m_vbo = std::make_unique<OpenGL::GLVertexBuffer>(vertices);
        m_ebo = std::make_unique<OpenGL::GLIndexBuffer>(indices);

        m_vao->AddVertexBuffer(*m_vbo);
        m_vao->AddIndexBuffer(*m_ebo);
        m_vao->Unbind();
    }

    void Mesh::Draw() const {
        m_vao->Bind();
        glDrawElements(GL_TRIANGLES, m_ebo->GetIndexCount(), GL_UNSIGNED_INT, 0);
        m_vao->Unbind();
    }

    void Mesh::Destroy() {
        m_ebo.reset();
        m_vbo.reset();
        m_vao.reset();
    }
}