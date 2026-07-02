#include <deoxy/deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
        }

        void OnUpdate(float dt) override {
            auto& renderer = GetRenderer();
            auto& window = GetWindow();
            auto& input = GetInput();
            auto& time = GetTime();
            
            std::string title = "Deoxy Engine | FPS: " + std::to_string(time.GetFPSApprox());
            window.SetWindowTitle(title);

            float realTime = time.Get();
            float speed = 1.5f;
            float r = Deoxy::Math::Sin(realTime * speed + 0.0f) * 0.5f + 0.5f;
            float g = Deoxy::Math::Sin(realTime * speed + 2.0f) * 0.5f + 0.5f;
            float b = Deoxy::Math::Sin(realTime * speed + 4.0f) * 0.5f + 0.5f;
            renderer.SetClearColor({r, g, b, 1.0f});
            
            if (input.WasKeyPressed(Deoxy::KeyCode::V)) {
                bool currentVSync = window.GetProperties().VSync;
                window.SetWindowVsync(!currentVSync);
            }

            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) Quit();
        }

        void OnRender() override {}
        void OnQuit() override {}
};

int main() {
    Game game;
    return game.Run();
}