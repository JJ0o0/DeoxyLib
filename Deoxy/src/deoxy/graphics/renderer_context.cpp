#include <deoxy/graphics/renderer_context.hpp>
#include <deoxy/logging/enginelog.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Deoxy::Graphics {
    void RendererContext::Init() {
        int version = gladLoadGL(glfwGetProcAddress);
        if (!version) {
            DEOXY_ERROR("Failed to load GLAD");
            return;
        }

        glEnable(GL_DEPTH_TEST);

        DEOXY_INFO("GPU: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        DEOXY_INFO("GL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        std::vector<Vertex> vertices {
            { Math::Vector3{-0.5f, 0.5f, 0.0f }},
            { Math::Vector3{ 0.5f, 0.5f, 0.0f }},
            { Math::Vector3{ 0.5f,-0.5f, 0.0f }},
            { Math::Vector3{-0.5f,-0.5f, 0.0f }},
        };

        std::vector<uint32_t> indices {
            0, 1, 2,
            0, 2, 3
        };

        m_shader = std::make_unique<OpenGL::GLShader>("assets/shaders/default.vert", "assets/shaders/default.frag");
        m_vao = std::make_unique<OpenGL::GLVertexArray>();
        m_vbo = std::make_unique<OpenGL::GLVertexBuffer>(vertices);
        m_ebo = std::make_unique<OpenGL::GLIndexBuffer>(indices);

        m_vao->AddVertexBuffer(*m_vbo);
        m_vao->AddIndexBuffer(*m_ebo);
        m_vao->Unbind();
    }

    void RendererContext::Destroy() {
        m_ebo.reset();
        m_vbo.reset();
        m_vao.reset();
        m_shader.reset();
    }

    void RendererContext::Clear(const Color& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererContext::Draw() {
        m_shader->Bind();
        m_vao->Bind();
        glDrawElements(GL_TRIANGLES, m_ebo->GetIndexCount(), GL_UNSIGNED_INT, 0);
        m_vao->Unbind();
        m_shader->Unbind();
    }

    void RendererContext::OnResize(uint32_t width, uint32_t height) {
        glViewport(0, 0, width, height);
    }
}