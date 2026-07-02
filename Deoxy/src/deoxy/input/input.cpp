#include <deoxy/input/input.hpp>
#include <GLFW/glfw3.h>
#include <array>

namespace Deoxy {
    void Input::Update() {
        m_previousKeys = m_currentKeys;
        m_previousMouseButtons = m_currentMouseButtons;

        m_mouseDeltaX = 0.0f;
        m_mouseDeltaY = 0.0f;

        m_scrollX = 0.0f;
        m_scrollY = 0.0f;
    }

    bool Input::IsKeyDown(KeyCode key) { 
        if (!IsValidKey(key)) return false;

        return m_currentKeys[ToKeyIndex(key)]; 
    }

    bool Input::WasKeyPressed(KeyCode key) { 
        if (!IsValidKey(key)) return false;

        const size_t index = ToKeyIndex(key);
        return m_currentKeys[index] && !m_previousKeys[index];
    }

    bool Input::WasKeyReleased(KeyCode key) { 
        if (!IsValidKey(key)) return false;

        const size_t index = ToKeyIndex(key);
        return !m_currentKeys[index] && m_previousKeys[index];
    }

    bool Input::IsMouseButtonDown(MouseButton button) { 
        if (!IsValidMouseButton(button)) return false;

        return m_currentMouseButtons[ToMouseIndex(button)]; 
    }

    bool Input::WasMouseButtonPressed(MouseButton button) {
        if (!IsValidMouseButton(button)) return false;

        const size_t index = ToMouseIndex(button);
        return m_currentMouseButtons[index] && !m_previousMouseButtons[index];
    }

    bool Input::WasMouseButtonReleased(MouseButton button) {
        if (!IsValidMouseButton(button)) return false;

        const size_t index = ToMouseIndex(button);
        return !m_currentMouseButtons[index] && m_previousMouseButtons[index];
    }

    float Input::GetMouseX() { return m_mouseX; }
    float Input::GetMouseY() { return m_mouseY; }

    float Input::GetMouseDeltaX() { return m_mouseDeltaX; }
    float Input::GetMouseDeltaY() { return m_mouseDeltaY; }

    float Input::GetScrollX() { return m_scrollX; }
    float Input::GetScrollY() { return m_scrollY; }

    void Input::SetKeyState(KeyCode key, bool pressed) {
        if (!IsValidKey(key)) return;

        m_currentKeys[ToKeyIndex(key)] = pressed;
    }

    void Input::SetMouseButtonState(MouseButton button, bool pressed) {
        if (!IsValidMouseButton(button)) return;

        m_currentMouseButtons[ToMouseIndex(button)] = pressed;
    }

    void Input::SetMousePosition(float x, float y) {
        m_mouseX = x;
        m_mouseY = y;
        m_mouseDeltaX += x;
        m_mouseDeltaY += y;
    }

    void Input::SetScroll(float x, float y) {
        m_scrollX += x;
        m_scrollY += y;
    }

    KeyCode Input::ConvertGLFWKeyCode(int key) {
        switch (key) {
            case GLFW_KEY_Q: return KeyCode::Q;
            case GLFW_KEY_W: return KeyCode::W;
            case GLFW_KEY_E: return KeyCode::E;
            case GLFW_KEY_R: return KeyCode::R;
            case GLFW_KEY_T: return KeyCode::T;
            case GLFW_KEY_Y: return KeyCode::Y;
            case GLFW_KEY_U: return KeyCode::U;
            case GLFW_KEY_I: return KeyCode::I;
            case GLFW_KEY_O: return KeyCode::O;
            case GLFW_KEY_P: return KeyCode::P;

            case GLFW_KEY_A: return KeyCode::A;
            case GLFW_KEY_S: return KeyCode::S;
            case GLFW_KEY_D: return KeyCode::D;
            case GLFW_KEY_F: return KeyCode::F;
            case GLFW_KEY_G: return KeyCode::G;
            case GLFW_KEY_H: return KeyCode::H;
            case GLFW_KEY_J: return KeyCode::J;
            case GLFW_KEY_K: return KeyCode::K;
            case GLFW_KEY_L: return KeyCode::L;

            case GLFW_KEY_SEMICOLON: return KeyCode::Ccedilla;

            case GLFW_KEY_Z: return KeyCode::Z;
            case GLFW_KEY_X: return KeyCode::X;
            case GLFW_KEY_C: return KeyCode::C;
            case GLFW_KEY_V: return KeyCode::V;
            case GLFW_KEY_B: return KeyCode::B;
            case GLFW_KEY_N: return KeyCode::N;
            case GLFW_KEY_M: return KeyCode::M;

            case GLFW_KEY_LEFT_SHIFT: return KeyCode::LeftShift;
            case GLFW_KEY_RIGHT_SHIFT: return KeyCode::RightShift;

            case GLFW_KEY_LEFT_CONTROL: return KeyCode::LeftControl;
            case GLFW_KEY_RIGHT_CONTROL: return KeyCode::RightControl;

            case GLFW_KEY_LEFT_ALT: return KeyCode::LeftAlt;
            case GLFW_KEY_RIGHT_ALT: return KeyCode::RightAlt;

            case GLFW_KEY_1: return KeyCode::One;
            case GLFW_KEY_2: return KeyCode::Two;
            case GLFW_KEY_3: return KeyCode::Three;
            case GLFW_KEY_4: return KeyCode::Four;
            case GLFW_KEY_5: return KeyCode::Five;
            case GLFW_KEY_6: return KeyCode::Six;
            case GLFW_KEY_7: return KeyCode::Seven;
            case GLFW_KEY_8: return KeyCode::Eight;
            case GLFW_KEY_9: return KeyCode::Nine;
            case GLFW_KEY_0: return KeyCode::Zero;

            case GLFW_KEY_F1: return KeyCode::F1;
            case GLFW_KEY_F2: return KeyCode::F2;
            case GLFW_KEY_F3: return KeyCode::F3;
            case GLFW_KEY_F4: return KeyCode::F4;
            case GLFW_KEY_F5: return KeyCode::F5;
            case GLFW_KEY_F6: return KeyCode::F6;
            case GLFW_KEY_F7: return KeyCode::F7;
            case GLFW_KEY_F8: return KeyCode::F8;
            case GLFW_KEY_F9: return KeyCode::F9;
            case GLFW_KEY_F10: return KeyCode::F10;
            case GLFW_KEY_F11: return KeyCode::F11;
            case GLFW_KEY_F12: return KeyCode::F12;

            case GLFW_KEY_ENTER: return KeyCode::Enter;
            case GLFW_KEY_SPACE: return KeyCode::Space;
            case GLFW_KEY_ESCAPE: return KeyCode::Escape;

            case GLFW_KEY_LEFT_SUPER:
            case GLFW_KEY_RIGHT_SUPER:
                return KeyCode::Super;

            case GLFW_KEY_UP: return KeyCode::Up;
            case GLFW_KEY_DOWN: return KeyCode::Down;
            case GLFW_KEY_LEFT: return KeyCode::Left;
            case GLFW_KEY_RIGHT: return KeyCode::Right;

            default: return KeyCode::Unknown;
        }
    }

    MouseButton Input::ConvertGLFWMouseButton(int btn) {
        switch (btn) {
            case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
            case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
            case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
            default: return MouseButton::Unknown;
        }
    }
}