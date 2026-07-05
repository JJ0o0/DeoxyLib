#include <deoxy/graphics/renderer.hpp>
#include <deoxy/graphics/renderer_context.hpp>
#include <memory>

namespace Deoxy::Graphics {
    Renderer::Renderer() = default;
    Renderer::~Renderer() = default;

    void Renderer::Init() {
        m_context = std::make_unique<RendererContext>();
        m_context->Init();
    }

    void Renderer::Destroy() {
        m_context->Destroy();
    }

    void Renderer::OnResize(uint32_t width, uint32_t height) {
        m_context->OnResize(width, height);
    }

    void Renderer::Clear() {
        m_context->Clear(m_clearColor);
    }

    void Renderer::DrawMesh(Mesh& mesh) {
        m_context->DrawMesh(mesh);
    }
    
    void Renderer::SetClearColor(const Color& color) {
        m_clearColor = color;
    }
}