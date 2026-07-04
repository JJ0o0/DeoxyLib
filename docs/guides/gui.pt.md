# Interface e GUI

A Deoxy traz integração nativa com a **Dear ImGui**, permitindo a criação rápida de interfaces de depuração, menus e ferramentas para o seu jogo. O controle do sistema é dividido entre a interface principal (`GUI`) e suas customizações visuais (`GUISettings`).

Toda a lógica de interface deve ser isolada dentro do método **`OnRenderGUI()`** do ciclo de vida da sua aplicação.

---

## Customizando o Visual (`GUISettings`)

A biblioteca permite alterar o comportamento e os temas da interface na inicialização. Você pode acessar essas opções chamando `GetGUISettings()` dentro do `OnStart()`:

* **Temas Disponíveis (`GUITheme`)**:
    * `Deoxy::GUITheme::Default`: O tema clássico da Dear ImGui.
    * `Deoxy::GUITheme::Rest`: Um estilo escuro moderno (baseado no *Rest style* por AaronBeardless).
* **Suporte a Docking**: Permite arrastar, acoplar e organizar janelas da interface de forma livre pela tela.

### Exemplo de Configuração:

```cpp
void OnStart() override {
    // Ativa o tema moderno Rest
    GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);

    // Ativa o suporte a acoplamento de janelas (Docking)
    GetGUISettings().SetDocked(true);
}
```

---

## Desenhando Elementos de Interface (`GUI`):

Dentro do método OnRenderGUI(), a Deoxy já inicializa e encerra o frame do ImGui automaticamente debaixo dos panos. Você pode usar tanto os comandos padrão da API do ImGui quanto as funções utilitárias da Deoxy via GetGUI().

### 1. Desenhando Texto Direto na Tela (Overlays)

Para desenhar textos (como contadores de FPS ou status de debug) flutuando na tela sem precisar abrir uma janela do ImGui, use o método `DrawText`. Ele aceita tanto `Color` (valores de 0.0f a 1.0f) quanto `Color32` (valores de 0 a 255):

```cpp
void OnRenderGUI() override {
    // Desenha usando Deoxy::Color (RGBA normalizado)
    GetGUI().DrawText(10, 10, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), "FPS: 60");

    // Desenha usando Deoxy::Color32 (RGBA de 8-bits)
    GetGUI().DrawText(10, 30, Deoxy::Color32(255, 255, 0, 255), "Debug Mode Actived");
}
```

### 2. Posicionando Janelas com Precisão

Se você precisar criar uma janela centralizada (como um menu de Pause ou Game Over), o método `SetNextWindowCentered` calcula a posição automaticamente com base na resolução atual da janela:

```cpp
void OnRenderGUI() override {
    if (m_gamePaused) {
        // Centraliza a próxima janela do ImGui com um tamanho de 200x150
        GetGUI().SetNextWindowCentered({200, 150});

        ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ImGui::Button("Resume")) m_gamePaused = false;
        if (ImGui::Button("Quit")) Quit();
        ImGui::End();
    }
}
```

!!! note "Nota sobre o ImGui"
    Como a Deoxy gerencia o contexto nativo, você está livre para utilizar qualquer função da API padrão da `ImGui::`(como `ImGui::Begin`, `ImGui::SliderFloat`, `ImGui::ColorEdit4`) diretamente no seu escopo, desde que estejam dentro de `OnRenderGUI()`.