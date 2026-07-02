#include <deoxy/deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
            GetWindow().SetWindowTitle(m_windowTitle);
            GetWindow().SetWindowVsync(m_vsync);
            GetRenderer().SetClearColor(m_clearColor);
        }

        void OnUpdate(float dt) override {
        }

        void OnRender() override {}

        void OnRenderGUI() override {
            ImGui::Begin("Settings");

            ImGui::Text("FPS: %d", GetTime().GetFPSApprox());

            if (ImGui::InputText("Window Title", &m_windowTitle)) { 
                GetWindow().SetWindowTitle(m_windowTitle);
            }

            if (ImGui::Checkbox("VSync", &m_vsync)) {
                GetWindow().SetWindowVsync(m_vsync);
            }

            if(ImGui::ColorEdit4("Edit Color", Deoxy::Math::GetPointer(m_clearColor))) {
                GetRenderer().SetClearColor(m_clearColor);
            }

            if (ImGui::Button("Quit App")) {
                Quit();
            }

            ImGui::End();
        }

        void OnQuit() override {}
    private:
        std::string m_windowTitle = "Deoxy Engine";
        bool m_vsync = true;
        Deoxy::Color m_clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
};

int main() {
    Game game;
    return game.Run();
}