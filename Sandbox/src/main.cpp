#include <deoxy/deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
        }

        void OnUpdate(float dt) override {
            auto& input = GetInput();
            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) Quit();
        }

        void OnRender() override {}
        void OnQuit() override {}
};

int main() {
    Game game;
    return game.Run();
}