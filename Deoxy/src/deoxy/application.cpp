#include "imgui.h"
#include <deoxy/application.hpp>
#include <deoxy/logging/logger.hpp>
#include <deoxy/logging/enginelog.hpp>

namespace Deoxy {
    int Application::Run() {
        Logging::Logger::Init();
        DEOXY_INFO("Initializing...");

        m_window = std::make_unique<Platform::Window>();

        m_renderer = std::make_unique<Graphics::Renderer>();
        m_renderer->Init();

        m_gui = std::make_unique<GUI>();
        m_gui->Init(m_window->GetHandle());

        m_time.Reset();
        OnStart();

        while (m_running && !m_window->ShouldClose()) {
            m_time.Update();
            m_input.Update();
            m_window->PollEvents();

            if (m_window->WasResized()) {
                auto& props = m_window->GetProperties();

                m_renderer->OnResize(props.Width, props.Height);
                m_window->ClearResizeFlag();
            }

            float dt = m_time.GetDeltaTime();
            OnUpdate(dt);

            m_renderer->Clear();
            OnRender();

            m_gui->NewFrame();
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
            OnRenderGUI();
            m_gui->EndFrame();
            
            m_window->SwapBuffers();
        }

        DEOXY_INFO("Quitting...");
        OnQuit();
        m_gui->Destroy();
        m_renderer->Destroy();
        m_window.reset();

        return 0;
    }

    void Application::Quit() { m_running = false; }
}