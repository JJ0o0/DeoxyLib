#pragma once

struct GLFWwindow;
namespace Deoxy {
    class GUI {
        public:
            void Init(GLFWwindow* glfwWindow);
            void Destroy();

            void NewFrame();
            void EndFrame();
    };
}