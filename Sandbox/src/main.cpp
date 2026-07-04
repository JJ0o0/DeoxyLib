#include <deoxy/deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
            GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);

            m_clearColor = GetRenderer().GetClearColor();
        }

        void OnUpdate(float dt) override {
            auto input = GetInput();

            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) m_showSettings = !m_showSettings;
            if (input.WasKeyPressed(Deoxy::KeyCode::V)) GetWindow().ToggleVsync();
        }

        void OnRender() override {}

        void OnRenderGUI() override {
            GetGUI().DrawText(
                10, 10, 
                Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), 
                std::format("FPS: {:d}", GetTime().GetFPSApprox())
            );

            GetGUI().DrawText(
                10, 30,
                Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), 
                std::format("Vsync: {:s}", GetWindow().GetProperties().VSync ? "On" : "Off")
            );

            if (m_showSettings) {
                GetGUI().SetNextWindowCentered({120, 120});
                ImGui::Begin("Settings", nullptr, 
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoCollapse
                );

                if (ImGui::ColorEdit4("Clear Color", Deoxy::Math::GetPointer(m_clearColor), ImGuiColorEditFlags_NoAlpha)) {
                    GetRenderer().SetClearColor(m_clearColor);
                }

                if (ImGui::Button("Close Settings")) m_showSettings = false;

                if (ImGui::Button("Quit Game")) Quit();
                
                ImGui::End();
            }
        }

        void OnQuit() override {}
    private:
        Deoxy::Color m_clearColor;
        bool m_showSettings = false;
};

int main() {
    Game game;
    return game.Run();
}