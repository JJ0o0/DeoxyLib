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
            
            m_fpsAccumulatedTime += dt;
            m_frameCount++;
            
            if (m_fpsAccumulatedTime >= 1.0f) {
                m_fps = static_cast<float>(m_frameCount) / m_fpsAccumulatedTime;
                
                std::string title = "Deoxy Engine | FPS: " + std::to_string(static_cast<int>(m_fps));
                window.SetWindowTitle(title);
                
                m_fpsAccumulatedTime = 0.0f;
                m_frameCount = 0;
            }

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
    private:
        uint32_t m_frameCount = 0;
        float m_fpsAccumulatedTime = 0.0f;
        float m_fps = 0.0f;
};

int main() {
    Game game;
    return game.Run();
}