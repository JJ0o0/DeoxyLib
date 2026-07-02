#include <deoxy/time.hpp>
#include <deoxy/utilities/math.hpp>
#include <GLFW/glfw3.h>

namespace Deoxy {
    void Time::Reset() {
        m_lastTime = glfwGetTime();
        m_deltaTime = 0.0f;
    }

    void Time::Update() {
        const double currentTime = glfwGetTime();

        m_deltaTime = static_cast<float>(currentTime - m_lastTime);
        m_lastTime = currentTime;

        m_frameCount++;
        m_fpsTimer += m_deltaTime;

        if (m_fpsTimer >= 0.25f) {
            m_fps = static_cast<float>(m_frameCount) / m_fpsTimer;
            m_frameCount = 0;
            m_fpsTimer = 0.0f;
        }
    }

    int Time::GetFPSApprox() { return Math::Round(m_fps); }
    float Time::GetFPS() { return m_fps; }
    float Time::GetDeltaTime() { return m_deltaTime; }
    float Time::Get() { return static_cast<float>(glfwGetTime()); }
}