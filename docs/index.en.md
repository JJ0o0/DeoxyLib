# Deoxy Docs - v0.1

<div align="center">
  <img src="assets/images/deoxy_logo.png" alt="Logo da Deoxy" width="200">
</div>
<br>

[Deoxy](https://github.com/JJ0o0/DeoxyLib) is a C++ library made for creating applications and games.

It provides simple abstractions for windowing, rendering, input, math utilities, among others.

!!! info "Project Status"
    Deoxy is currently in version **v0.1**. The core API is being refined and new rendering features are under active development.

---

## Quick Start

Here is a functional example of a Deoxy application. It creates a window, displays information on the screen, manages the VSync state, and renders a dynamic settings menu:

```cpp
#include <deoxy/deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
            GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);

            // Stores the renderer's initial clear color
            m_clearColor = GetRenderer().GetClearColor();
        }

        void OnUpdate(float dt) override {
            auto input = GetInput();

            // Keyboard shortcuts
            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) m_showSettings = !m_showSettings;
            if (input.WasKeyPressed(Deoxy::KeyCode::V)) GetWindow().ToggleVsync();
        }

        void OnRender() override {
            // Your game rendering goes here
        }

        void OnRenderGUI() override {
            // Draws simple text on the screen
            GetGUI().DrawText(10, 10, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), std::format("FPS: {:d}", GetTime().GetFPSApprox()));
            GetGUI().DrawText(10, 30, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), std::format("Vsync: {:s}", GetWindow().GetProperties().VSync ? "On" : "Off"));

            // Renders the menu using the integrated ImGui
            if (m_showSettings) {
                GetGUI().SetNextWindowCentered({120, 120});
                ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

                if (ImGui::ColorEdit4("Clear Color", Deoxy::Math::GetPointer(m_clearColor), ImGuiColorEditFlags_NoAlpha)) {
                    GetRenderer().SetClearColor(m_clearColor);
                }

                if (ImGui::Button("Close Settings")) m_showSettings = false;
                if (ImGui::Button("Quit Game")) Quit();
                
                ImGui::End();
            }
        }

        void OnQuit() override {
            // Executed upon closing the game
        }

    private:
        Deoxy::Color m_clearColor;
        bool m_showSettings = false;
};

int main() {
    Game game;
    return game.Run();
}
```
---

## Next Steps

* [Installation Guide](getting-started/installation.md): How to clone, compile dependencies, and link Deoxy in your CMake project.
* [Quick Start](getting-started/quick-start.md): Understand line-by-line the structure of the Application class and how the framework's render loop operates.

!!! note "Looking for code documentation?"
    If you want to explore function signatures, low-level class definitions, and namespace hierarchies, visit our [API Reference](.#../../api/index.html) generated directly from the source code.