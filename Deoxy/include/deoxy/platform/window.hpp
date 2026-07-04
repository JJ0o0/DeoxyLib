#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

namespace Deoxy::Platform {
    /**
     * @ingroup Platform
     * @brief Available window display modes.
     */
    enum class WindowMode {
        /**
         * @brief Standard resizable window.
         */
        Windowed,

        /**
         * @brief Borderless window covering the entire monitor.
         */
        BorderlessFullscreen,

        /**
         * @brief Exclusive fullscreen mode.
         */
        ExclusiveFullscreen
    };

    /**
     * @ingroup Platform
     * @brief Describes the initial state of a window.
     */
    struct WindowProperties {
        /// Window title.
        std::string Title = "Deoxy";

        /// Path to the window icon.
        std::string Icon = "";

        /// Window width in pixels.
        uint32_t Width = 800;

        /// Window height in pixels.
        uint32_t Height = 600;

        /// Initial window mode.
        WindowMode Mode = WindowMode::Windowed;

        /// Whether vertical synchronization is enabled.
        bool VSync = true;
    };

    /**
     * @ingroup Platform
     * @brief Represents the main application window.
     *
     * Provides window management, input event polling and
     * fullscreen control.
     */
    class Window {
        public:
            /**
             * @brief Creates a new window.
             * 
             * @param properties Initial window properties.
             */
            Window(const WindowProperties& properties = {});

            /**
             * @brief Destroys the window and releases its resources.
             */
            ~Window();
            
            /**
             * @brief Swaps the front and back buffers.
             */
            void SwapBuffers() const;

            /**
             * @brief Processes pending window events.
             */
            void PollEvents() const;

            /**
             * @brief Returns whether the window should close.
             */
            bool ShouldClose() const;

            /**
             * @brief Returns whether the framebuffer was resized.
             */
            bool WasResized() const;

            /**
             * @brief Clears the resize flag.
             */
            void ClearResizeFlag();

            /**
             * @brief Toggles between windowed and exclusive fullscreen mode.
             */
            void ToggleFullscreen();

            /**
             * @brief Toggles vertical synchronization.
             */
            void ToggleVsync();

            /**
             * @brief Sets the window title.
             * 
             * @param title New window title.
             */
            void SetWindowTitle(const std::string& title);

            /**
             * @brief Sets the window size.
             * 
             * @param width New width in pixels.
             * @param height New height in pixels.
             */
            void SetWindowSize(uint32_t width, uint32_t height);

            /**
             * @brief Sets the window mode.
             * 
             * @param mode New window mode.
             */
            void SetWindowMode(WindowMode mode);

            /**
             * @brief Sets the window icon.
             * 
             * @param filepath Path to the image file.
             */
            void SetWindowIcon(const std::string& filepath);

            /**
             * @brief Enables or disables vertical synchronization.
             * 
             * @param enabled True to enable VSync.
             */
            void SetWindowVsync(bool enabled);

            /**
             * @brief Returns the current window properties.
             */
            WindowProperties& GetProperties() { return m_properties; };
            const WindowProperties& GetProperties() const { return m_properties; };

            /**
             * @brief Returns the native GLFW window handle.
             * 
             * @return Pointer to the underlying GLFW window. 
             */
            GLFWwindow* GetHandle() { return m_handle; }
            const GLFWwindow* GetHandle() const { return m_handle; }
        private:
            GLFWwindow* m_handle = nullptr;
            WindowProperties m_properties = {};

            int m_lastWindowedX = 0;
            int m_lastWindowedY = 0;
            int m_lastWindowedWidth = 800;
            int m_lastWindowedHeight = 600;

            bool m_resized = false;

            void saveWindowMode();

            static void framebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);
            static void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
            static void cursorPositionCallback(GLFWwindow* glfwWindow, double x, double y);
            static void scrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset);
    };
}