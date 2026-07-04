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

        DEOXY_INFO("GPU: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        DEOXY_INFO("GL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }

    void RendererContext::Destroy() {

    }

    void RendererContext::Clear(const Color& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererContext::OnResize(uint32_t width, uint32_t height) {
        glViewport(0, 0, width, height);
    }
}