#pragma once

#include "time.hpp"
#include "graphics/renderer.hpp"
#include "platform/window.hpp"
#include "input/input.hpp"
#include "imgui/gui_handler.hpp"
#include <memory>

namespace Deoxy {
    /**
     * @ingroup Core
     * @brief Base class for all Deoxy applications.
     * 
     * Derive from this class and override the lifecycle callbacks
     * to create a game or editor application.
     */
    class Application {
        public:
            /**
             * @brief Starts the main application loop.
             * 
             * Initializes the engine and runs until Quit() is called
             * or the window is closed.
             *
             * @return 0 if the application exits successfully
             */
            int Run();

            /**
             * @brief Requests the application to stop.
             * 
             * The main loop will exited at the end of the current frame.
             */
            void Quit();
        protected:
            virtual ~Application() = default;

            /**
             * @brief Called once when the application starts.
             */
            virtual void OnStart() = 0;

            /**
             * @brief Called every frame.
             *
             * @param dt Delta time in seconds.
             */
            virtual void OnUpdate(float dt) = 0;

            /**
             * @brief Called every frame to render the scene.
             */
            virtual void OnRender() = 0;

            /**
             * @brief Called every frame to render ImGui widgets.
             */
            virtual void OnRenderGUI() = 0;

            /**
             * @brief Called once before the application exits.
             */
            virtual void OnQuit() = 0;

            /**
             * @brief Returns the main application window.
             */
            Platform::Window& GetWindow() { return *m_window; }
            const Platform::Window& GetWindow() const { return *m_window; }

            /**
             * @brief Returns the renderer instance.
             */
            Graphics::Renderer& GetRenderer() { return *m_renderer; }
            const Graphics::Renderer& GetRenderer() const { return *m_renderer; }

            /**
             * @brief Returns the input manager.
             */
            Input& GetInput() { return m_input; }
            const Input& GetInput() const { return m_input; }

            /**
             * @brief Returns the time manager.
             */
            Time& GetTime() { return m_time; }
            const Time& GetTime() const { return m_time; }

            /**
             * @brief Returns the GUI manager.
             */
            GUI& GetGUI() { return *m_gui; }
            const GUI& GetGUI() const { return *m_gui; }

            /**
             * @brief Returns the GUI settings.
             */
            GUISettings& GetGUISettings() { return m_gui->GetSettings(); }
            const GUISettings& GetGUISettings() const { return m_gui->GetSettings(); }
        private:
            std::unique_ptr<Platform::Window> m_window;
            std::unique_ptr<Graphics::Renderer> m_renderer;
            std::unique_ptr<GUI> m_gui;
            Input m_input;
            Time m_time;

            bool m_running = true;
    };
}