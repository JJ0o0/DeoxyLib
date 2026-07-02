#include <deoxy/application.hpp>
#include <deoxy/logging/logger.hpp>
#include <deoxy/logging/enginelog.hpp>

namespace Deoxy {
    int Application::Run() {
        Logging::Logger::Init();
        DEOXY_INFO("Initializing...");
        m_window = std::make_unique<Platform::Window>();
        m_time.Reset();
        OnStart();

        while (m_running && !m_window->ShouldClose()) {
            m_time.Update();
            m_input.Update();
            m_window->PollEvents();

            if (m_window->WasResized()) {
                m_window->ClearResizeFlag();
            }

            float dt = m_time.GetDeltaTime();
            OnUpdate(dt);

            OnRender();
            
            m_window->SwapBuffers();
        }

        DEOXY_INFO("Quitting...");
        OnQuit();
        m_window.reset();

        return 0;
    }

    void Application::Quit() { m_running = false; }
}