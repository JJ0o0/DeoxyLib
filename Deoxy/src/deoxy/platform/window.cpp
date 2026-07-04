#include <deoxy/platform/window.hpp>
#include <deoxy/input/input.hpp>
#include <deoxy/logging/enginelog.hpp>
#include <GLFW/glfw3.h>
#include <stb_image.h>

namespace Deoxy::Platform {
    static void errorCallback(int code, const char* description) {
        DEOXY_ERROR("GLFW returned an error with code {}:\nInformation: {}", code, description);
    }

    void Window::saveWindowMode() {
        if (m_properties.Mode != WindowMode::Windowed) return;

        glfwGetWindowPos(m_handle, &m_lastWindowedX, &m_lastWindowedY);
        glfwGetWindowSize(m_handle, &m_lastWindowedWidth, &m_lastWindowedHeight);
    }

    void Window::framebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height) {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

        window->GetProperties().Width = width;
        window->GetProperties().Height = height;
        window->m_resized = true;
    }

    void Window::keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
        const auto keycode = Input::ConvertGLFWKeyCode(key);
        if (keycode == KeyCode::Unknown) return;

        const bool pressed = action != GLFW_RELEASE;
        Input::SetKeyState(keycode, pressed);
    }

    void Window::mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods) {
        const auto mousebutton = Input::ConvertGLFWMouseButton(button);
        if (mousebutton == MouseButton::Unknown) return;

        const auto pressed = action != GLFW_RELEASE;
        Input::SetMouseButtonState(mousebutton, pressed);
    }

    void Window::cursorPositionCallback(GLFWwindow* glfwWindow, double x, double y) { 
        Input::SetMousePosition(static_cast<float>(x), static_cast<float>(y)); 
    }

    void Window::scrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset) { 
        Input::SetScroll(static_cast<float>(xOffset), static_cast<float>(yOffset)); 
    }

    Window::Window(const WindowProperties& properties) {
        glfwSetErrorCallback(errorCallback);

        if (!glfwInit()) {
            DEOXY_CRITICAL("GLFW was not initialized!");
            std::abort();
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_handle = glfwCreateWindow(
            properties.Width,
            properties.Height,
            properties.Title.c_str(),
            nullptr, nullptr
        );

        if (!m_handle) {
            DEOXY_CRITICAL("Window was not created!");
            glfwTerminate();
            std::abort();
        }

        glfwMakeContextCurrent(m_handle);

        glfwSetWindowUserPointer(m_handle, this);
        glfwSetFramebufferSizeCallback(m_handle, framebufferSizeCallback);
        glfwSetKeyCallback(m_handle, keyCallback);
        glfwSetMouseButtonCallback(m_handle, mouseButtonCallback);
        glfwSetCursorPosCallback(m_handle, cursorPositionCallback);
        glfwSetScrollCallback(m_handle, scrollCallback);

        SetWindowMode(properties.Mode);
        SetWindowVsync(properties.VSync);
        if (!properties.Icon.empty()) SetWindowIcon(properties.Icon);

        m_properties = properties;
        DEOXY_INFO("Created {}x{} window.", m_properties.Width, m_properties.Height);
    }

    Window::~Window() {
        if (m_handle) {
            glfwDestroyWindow(m_handle);
            m_handle = nullptr;
        }

        glfwTerminate();
    }

    void Window::SwapBuffers() const { glfwSwapBuffers(m_handle); }
    void Window::PollEvents() const { glfwPollEvents(); }
    bool Window::ShouldClose() const { return glfwWindowShouldClose(m_handle); }
    bool Window::WasResized() const { return m_resized; }

    void Window::ClearResizeFlag() { m_resized = false; }

    void Window::ToggleFullscreen() {
        if (m_properties.Mode == WindowMode::ExclusiveFullscreen) SetWindowMode(WindowMode::Windowed);
        else SetWindowMode(WindowMode::ExclusiveFullscreen);
    }

    void Window::ToggleVsync() {
        bool enabled = m_properties.VSync;
        SetWindowVsync(!enabled);
    }

    void Window::SetWindowTitle(const std::string& title) {
        if (title.empty()) {
            DEOXY_ERROR("Could not change window title: Empty title.");
            return;
        }

        if (m_properties.Title == title) return;

        glfwSetWindowTitle(m_handle, title.c_str());
        m_properties.Title = title;
    }

    void Window::SetWindowSize(uint32_t width, uint32_t height) {
        if (width == 0 || height == 0) {
            DEOXY_ERROR("Could not resize: Invalid window size.");
            return;
        }

        if (m_properties.Width == width && m_properties.Height == height) { return; }

        glfwSetWindowSize(m_handle, width, height);

        m_properties.Width = width;
        m_properties.Height = height;
        m_resized = true;
    }

    void Window::SetWindowMode(WindowMode mode) {
        if (m_properties.Mode == mode) return;
        if (m_properties.Mode == WindowMode::Windowed && mode != WindowMode::Windowed) saveWindowMode();

        switch (mode) {
            case WindowMode::Windowed: {
                glfwSetWindowAttrib(m_handle, GLFW_DECORATED, GLFW_TRUE);
                glfwSetWindowAttrib(m_handle, GLFW_RESIZABLE, GLFW_TRUE);

                glfwSetWindowMonitor(
                    m_handle,
                    nullptr,
                    m_lastWindowedX,
                    m_lastWindowedY,
                    m_lastWindowedWidth,
                    m_lastWindowedHeight,
                    0
                );

                break;
            }
            case WindowMode::BorderlessFullscreen: {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* vid = glfwGetVideoMode(monitor);
                
                int monitorX = 0, monitorY = 0;
                glfwGetMonitorPos(monitor, &monitorX, &monitorY);

                glfwSetWindowAttrib(m_handle, GLFW_DECORATED, GLFW_FALSE);
                glfwSetWindowAttrib(m_handle, GLFW_RESIZABLE, GLFW_FALSE);

                glfwSetWindowMonitor(
                    m_handle,
                    nullptr,
                    monitorX,
                    monitorY,
                    vid->width,
                    vid->height,
                    0
                );

                glfwFocusWindow(m_handle);

                break;
            }
            case WindowMode::ExclusiveFullscreen: {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* vid = glfwGetVideoMode(monitor);

                glfwSetWindowMonitor(
                    m_handle,
                    monitor,
                    0,
                    0,
                    vid->width,
                    vid->height,
                    vid->refreshRate
                );
                
                break;
            }
        }

        m_properties.Mode = mode;
        m_resized = true;
    }

    void Window::SetWindowIcon(const std::string& filepath) {
        if (m_properties.Icon == filepath) return;

        if (filepath.empty()) {
            glfwSetWindowIcon(m_handle, 0, nullptr);
            m_properties.Icon.clear();
            return;
        }

        GLFWimage icon{};

        int channels = 0;
        icon.pixels = stbi_load(filepath.c_str(), &icon.width, &icon.height, &channels, 4);

        if (!icon.pixels) {
            DEOXY_ERROR("Failed to load window icon at \"{}\": {}", filepath, stbi_failure_reason() ? stbi_failure_reason() : "Unknown");
            return;
        }

        glfwSetWindowIcon(m_handle, 1, &icon);
        stbi_image_free(icon.pixels);

        DEOXY_INFO("Window icon set: {}", filepath);

        m_properties.Icon = filepath;
    }

    void Window::SetWindowVsync(bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_properties.VSync = enabled;
    }
}