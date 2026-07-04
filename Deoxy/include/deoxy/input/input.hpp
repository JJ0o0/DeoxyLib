#pragma once

#include "../platform/window.hpp"
#include "keycode.hpp"
#include "mouse_button.hpp"
#include <array>
#include <cstddef>

namespace Deoxy {
    /**
     * @ingroup Input 
     * @brief Provides keyboard and mouse input state.
     *
     * The Input class allows querying the current and previous
     * state of keyboard keys and mouse buttons, as well as
     * mouse movement and scroll information.
     */
    class Input {
        public:
            /**
             * @brief Updates the input state.
             * 
             * Called internally once per frame.
             *
             * @note This function is called internally by the engine and
             * should not be invoked by user code.
             */
            void Update();

            /**
             * @brief Returns whether a key is currently held down.
             * 
             * @param key Key to query.
             * @return true if the key is down.
             */
            bool IsKeyDown(KeyCode key);

            /**
             * @brief Returns whether a key was pressed this frame.
             * 
             * @param key Key to query.
             * @return true if the key transitioned from up to down.
             */
            bool WasKeyPressed(KeyCode key);

            /**
             * @brief Returns whether a key was released this frame.
             * 
             * @param key Key to query.
             * @return true if the key transitioned from down to up.
             */
            bool WasKeyReleased(KeyCode key);

            /**
             * @brief Returns whether a mouse button is currently held down.
             * 
             * @param button button to query.
             * @return true if the mouse button is down.
             */
            bool IsMouseButtonDown(MouseButton button);

            /**
             * @brief Returns whether a mouse button was pressed this frame.
             * 
             * @param button button to query.
             * @return true if the mouse button transitioned from up to down.
             */
            bool WasMouseButtonPressed(MouseButton button);

            /**
             * @brief Returns whether a mouse button was released this frame.
             * 
             * @param button button to query.
             * @return true if the mouse button transitioned from down to up.
             */
            bool WasMouseButtonReleased(MouseButton button);

            /**
             * @brief Returns the current mouse X position.
             * 
             * @return Mouse position in pixels.
             */
            float GetMouseX();

            /**
             * @brief Returns the current mouse Y position.
             * 
             * @return Mouse position in pixels.
             */
            float GetMouseY();

            /**
             * @brief Returns the horizontal mouse movement since the last frame.
             * 
             * @return Delta in pixels.
             */
            float GetMouseDeltaX();

            /**
             * @brief Returns the vertical mouse movement since the last frame.
             * 
             * @return Delta in pixels.
             */
            float GetMouseDeltaY();

            /**
             * @brief Returns the horizontal scroll offset for the current frame.
             * 
             * @return Scroll offset in pixels.
             */
            float GetScrollX();

            /**
             * @brief Returns the vertical scroll offset for the current frame.
             * 
             * @return Scroll offset in pixels.
             */
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