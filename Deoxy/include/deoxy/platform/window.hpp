#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

namespace Deoxy::Platform {
    enum class WindowMode {
        Windowed,
        BorderlessFullscreen,
        ExclusiveFullscreen
    };

    struct WindowProperties {
        std::string Title = "DeoxyVK";
        std::string Icon = "";
        uint32_t Width = 800;
        uint32_t Height = 600;
        WindowMode Mode = WindowMode::Windowed;
        bool VSync = true;
    };

    class Window {
        public:
            Window(const WindowProperties& properties = {});
            ~Window();
            
            void SwapBuffers() const;
            void PollEvents() const;
            bool ShouldClose() const;
            bool WasResized() const;

            void ClearResizeFlag();
            void ToggleFullscreen();
            void SetWindowTitle(const std::string& title);
            void SetWindowSize(uint32_t width, uint32_t height);
            void SetWindowMode(WindowMode mode);
            void SetWindowIcon(const std::string& filepath);
            void SetWindowVsync(bool enabled);

            WindowProperties& GetProperties() { return m_properties; };
            const WindowProperties& GetProperties() const { return m_properties; };

            GLFWwindow* GetHandle() { return m_handle; }
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