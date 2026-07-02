#pragma once

#include "../platform/window.hpp"
#include "keycode.hpp"
#include "mouse_button.hpp"
#include <array>
#include <cstddef>

namespace Deoxy {
    class Input {
        public:
            void Update();

            bool IsKeyDown(KeyCode key);
            bool WasKeyPressed(KeyCode key);
            bool WasKeyReleased(KeyCode key);

            bool IsMouseButtonDown(MouseButton button);
            bool WasMouseButtonPressed(MouseButton button);
            bool WasMouseButtonReleased(MouseButton button);

            float GetMouseX();
            float GetMouseY();

            float GetMouseDeltaX();
            float GetMouseDeltaY();

            float GetScrollX();
            float GetScrollY();
        private:
            friend class Platform::Window;

            static inline std::array<bool, static_cast<size_t>(KeyCode::Count)> m_currentKeys{};
            static inline std::array<bool, static_cast<size_t>(KeyCode::Count)> m_previousKeys{};
            static inline std::array<bool, static_cast<size_t>(MouseButton::Count)> m_currentMouseButtons{};
            static inline std::array<bool, static_cast<size_t>(MouseButton::Count)> m_previousMouseButtons{};

            static inline float m_mouseX = 0.0f;
            static inline float m_mouseY = 0.0f;

            static inline float m_lastMouseX = 0.0f;
            static inline float m_lastMouseY = 0.0f;

            static inline float m_mouseDeltaX = 0.0f;
            static inline float m_mouseDeltaY = 0.0f;

            static inline float m_scrollX = 0.0f;
            static inline float m_scrollY = 0.0f;

            static size_t ToKeyIndex(KeyCode key) { return static_cast<size_t>(key); }
            static size_t ToMouseIndex(MouseButton btn) { return static_cast<size_t>(btn); }

            static bool IsValidKey(KeyCode key) { return key != KeyCode::Unknown; }
            static bool IsValidMouseButton(MouseButton btn) { return btn != MouseButton::Unknown; }

            static void SetKeyState(KeyCode key, bool pressed);
            static void SetMouseButtonState(MouseButton button, bool pressed);
            static void SetMousePosition(float x, float y);
            static void SetScroll(float x, float y);

            static KeyCode ConvertGLFWKeyCode(int key);
            static MouseButton ConvertGLFWMouseButton(int btn);
    };
}