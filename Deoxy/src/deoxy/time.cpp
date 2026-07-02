#include <deoxy/time.hpp>
#include <GLFW/glfw3.h>

namespace Deoxy {
    void Time::Reset() {
        s_lastTime = glfwGetTime();
        s_deltaTime = 0.0f;
    }

    void Time::Update() {
        const double currentTime = glfwGetTime();

        s_deltaTime = static_cast<float>(currentTime - s_lastTime);
        s_lastTime = currentTime;
    }

    float Time::GetDeltaTime() { return s_deltaTime; }
    float Time::Get() { return static_cast<float>(glfwGetTime()); }
}