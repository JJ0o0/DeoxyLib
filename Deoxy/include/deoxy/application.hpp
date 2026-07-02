#pragma once

#include "time.hpp"
#include "graphics/renderer.hpp"
#include "platform/window.hpp"
#include "input/input.hpp"
#include <memory>

namespace Deoxy {
    class Application {
        public:
            int Run();
            void Quit();
        protected:
            virtual ~Application() = default;

            virtual void OnStart() = 0;
            virtual void OnUpdate(float dt) = 0;
            virtual void OnRender() = 0;
            virtual void OnQuit() = 0;

            Platform::Window& GetWindow() { return *m_window; }
            const Platform::Window& GetWindow() const { return *m_window; }

            Graphics::Renderer& GetRenderer() { return *m_renderer; }
            const Graphics::Renderer& GetRenderer() const { return *m_renderer; }

            Input& GetInput() { return m_input; }
            const Input& GetInput() const { return m_input; }

            Time& GetTime() { return m_time; }
            const Time& GetTime() const { return m_time; }
        private:
            std::unique_ptr<Platform::Window> m_window;
            std::unique_ptr<Graphics::Renderer> m_renderer;
            Input m_input;
            Time m_time;

            bool m_running = true;
    };
}