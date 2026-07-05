#include <Deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
            GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);

            auto& obj = m_scene.CreateGameObject("Quad");
            obj.SetMesh(Deoxy::Graphics::CreateTriangle());
            obj.SetShader("assets/shaders/default.vert", "assets/shaders/default.frag");
        }

        void OnUpdate(float dt) override {
            auto input = GetInput();

            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) Quit();
            if (input.WasKeyPressed(Deoxy::KeyCode::V)) GetWindow().ToggleVsync();
        }

        void OnRender() override {
            GetRenderer().DrawScene(m_scene);
        }

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
        }

        void OnQuit() override {}
    private:
        Deoxy::Scene m_scene;

        bool m_showSettings = false;
};

int main() {
    Game game;
    return game.Run();
}