# Início Rápido

Agora que você já tem a Deoxy instalada e configurada no seu projeto, vamos entender como criar a estrutura básica de um jogo e como a biblioteca gerencia o ciclo de vida da sua aplicação.

---

## A Classe `Deoxy::Application`

Diferente de bibliotecas onde você precisa criar o loop `while` manualmente, a Deoxy adota uma abordagem orientada a objetos. Você cria uma classe para o seu jogo que herda de **`Deoxy::Application`** e sobrescreve as funções do ciclo de vida:

```cpp
#include <deoxy/deoxy.hpp>

class MeuJogo : public Deoxy::Application {
protected:
    void OnStart() override {
        // Executado UMA vez no início do jogo
    }

    void OnUpdate(float dt) override {
        // Executado a cada frame lógico (Inputs, Física, etc.)
    }

    void OnRender() override {
        // Executado a cada frame gráfico (Desenho do Jogo)
    }

    void OnRenderGUI() override {
        // Executado após o OnRender (Interface, Textos, ImGui)
    }

    void OnQuit() override {
        // Executado imediatamente antes de fechar
    }
};

int main() {
    MeuJogo jogo;
    return jogo.Run(); // Inicializa e roda o loop principal
}
```

---

## Entendendo as Etapas

### 1. Inicialização

Use esse espaço para carregar texturas, configurar o tema da interface ou definir propriedades da janela que só precisam ser executadas uma vez antes do jogo começar.

```cpp
void OnStart() override {
    GetWindow().SetWindowIcon("assets/icon.png");
    GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);
}
```

### 2. Lógica e Tempo Real

Aqui você processa as entradas do jogador e atualiza o estado do mundo. O parâmetro dt (Delta Time) representa o tempo que o último frame demorou para ser processado. Sempre multiplique a velocidade dos seus objetos por dt para garantir que o jogo rode na mesma velocidade em qualquer monitor (seja 60Hz ou 144Hz).

```cpp
void OnUpdate(float dt) override {
    auto input = GetInput();

    // Movimentação independente de frame rate usando dt
    if (input.IsKeyDown(Deoxy::KeyCode::W)) jogador.y += velocidade * dt;

    // Atalhos de disparo único
    if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) m_showSettings = !m_showSettings;
}
```

### 3. Renderização de Interface

A Deoxy possui uma camada dedicada para desenhar textos ou elementos de UI por cima do jogo, trazendo integração nativa com o ImGui. É perfeita para criar menus, telas de debug ou inventários.

```cpp
void OnRenderGUI() override {
    // Desenha um texto simples na tela coordenado por pixels
    GetGUI().DrawText(10, 10, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), "Olá, Deoxy!");

    // Janela flutuante do ImGui
    ImGui::Begin("Menu");
    if (ImGui::Button("Sair")) Quit(); // Fecha a aplicação de forma limpa
    ImGui::End();
}
```

---

## Próximo Passo

Com o ciclo de vida compreendido, adicione o código completo no seu ```main.cpp``` e rode seu projeto. No próximo módulo, vamos explorar detalhadamente como o **Sistema de Janela** funciona para configurarmos do nosso jeito.