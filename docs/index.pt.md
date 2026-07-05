# Deoxy Docs - v0.1

<div align="center">
  <img src="../assets/images/deoxy_logo.png" alt="Logo da Deoxy" width="200">
</div>
<br>

[Deoxy](https://github.com/JJ0o0/DeoxyLib) é uma biblioteca C++ feita para a criação de aplicativos e jogos.

Ela fornece abstrações simples para janela, renderização, input, utilitários de matemática, entre outros.

!!! info "Status do Projeto"
    A Deoxy está atualmente na versão **v0.1**. A API principal está sendo refinada e novos recursos de renderização estão em desenvolvimento ativo.

---

## Começo Rápido

Aqui está um exemplo funcional de uma aplicação Deoxy. Ela cria uma janela, exibe informações na tela, gerencia o estado de VSync e renderiza um menu de configurações dinâmico:

```cpp
#include <deoxy/deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {
            GetWindow().SetWindowIcon("assets/icon.png");
            GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);

            // Armazena a cor de limpeza inicial do renderizador
            m_clearColor = GetRenderer().GetClearColor();
        }

        void OnUpdate(float dt) override {
            auto input = GetInput();

            // Atalhos de teclado
            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) m_showSettings = !m_showSettings;
            if (input.WasKeyPressed(Deoxy::KeyCode::V)) GetWindow().ToggleVsync();
        }

        void OnRender() override {
            // Sua renderização de jogo vai aqui
        }

        void OnRenderGUI() override {
            // Desenha textos simples na tela
            GetGUI().DrawText(10, 10, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), std::format("FPS: {:d}", GetTime().GetFPSApprox()));
            GetGUI().DrawText(10, 30, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), std::format("Vsync: {:s}", GetWindow().GetProperties().VSync ? "On" : "Off"));

            // Renderiza menu utilizando ImGui integrado
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
            // Executado ao fechar o jogo
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

## Próximos Passos

* [Guia de Instalação](getting-started/installation.md): Como clonar, compilar as dependências e linkar a Deoxy no seu projeto CMake.
* [Início Rápido](getting-started/quick-start.md): Entenda linha por linha a estrutura da classe Application e como funciona o loop de renderização do framework.

!!! note "Procurando a documentação do código?"
    Se você deseja explorar as assinaturas de funções, definições de classes de baixo nível e a hierarquia dos namespaces, acesse a nossa [API Reference](.#../../api/index.html) gerada diretamente a partir dos fontes.