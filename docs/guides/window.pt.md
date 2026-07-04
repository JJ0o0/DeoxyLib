# Sistema de Janela

O gerenciamento da janela principal na Deoxy é feito pela classe `Deoxy::Platform::Window`. Você pode interagir com ela tanto definindo suas propriedades iniciais quanto alterando seu estado em tempo real durante a execução do jogo.

---

## Configuração Inicial

Por padrão, a Deoxy inicializa uma janela de `800x600` em modo janela com VSync ativado. No entanto, se o seu construtor herdar de `Deoxy::Application`, você pode customizar esse estado passando uma struct `WindowProperties`.

A estrutura aceita os seguintes campos:

* `Title` (std::string): Título da janela.
* `Icon` (std::string): Caminho para a imagem `.png`.
* `Width` / `Height` (uint32_t): Resolução em pixels.
* `Mode` (`WindowMode`): Estado da tela (`Windowed`, `BorderlessFullscreen`, ou `ExclusiveFullscreen`).
* `VSync` (bool): Ativa ou desativa a sincronização vertical.

---

## Manipulação em Tempo Real

Dentro de qualquer método do ciclo de vida da sua aplicação (como `OnStart` ou `OnUpdate`), você pode acessar a instância da janela ativa utilizando o método `GetWindow()`.

### Alterando Propriedades Básicas

```cpp
void OnStart() override {
    // Define o título dinamicamente
    GetWindow().SetWindowTitle("Deoxy Engine - Edição de Criação");

    // Redimensiona a janela
    GetWindow().SetWindowSize(1280, 720);

    // Altera o ícone da barra de tarefas
    GetWindow().SetWindowIcon("assets/textures/icon.png");
}
```

### Controle de Tela Cheia e VSync

A Deoxy facilita a alternância de modos de exibição por meio de funções de toggle (alternância), ideais para mapear em atalhos de teclado dentro do OnUpdate:

```cpp
void OnUpdate(float dt) override {
    auto input = GetInput();

    // Alterna entre Modo Janela e Fullscreen Exclusivo com F11
    if (input.WasKeyPressed(Deoxy::KeyCode::F11)) {
        GetWindow().ToggleFullscreen();
    }

    // Liga/Desliga o VSync com a tecla V
    if (input.WasKeyPressed(Deoxy::KeyCode::V)) {
        GetWindow().ToggleVsync();
    }
}
```

!!! note "Alternativa"
    Para controle direto sem alternância, você também pode usar:

    * `GetWindow().SetWindowMode(Deoxy::Platform::WindowMode::BorderlessFullscreen);`
    * `GetWindow().SetWindowVsync(false);`

### Lendo Propriedades da Janela

Se precisar checar o estado atual da janela (por exemplo, para exibir o status na sua interface gráfica), você pode acessar as propriedades internas com `GetProperties()`:

```cpp 
void OnRenderGUI() override {
    auto& props = GetWindow().GetProperties();

    GetGUI().DrawText(10, 50, 
        Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), 
        std::format("Resolução Atual: {}x{}", props.Width, props.Height)
    );
}
```

---

## Recursos Avançados

Se você precisar estender a biblioteca ou fazer algo muito específico que dependa diretamente da API do GLFW, a Deoxy fornece acesso direto ao ponteiro nativo da janela através do método `GetHandle()`:

```cpp
GLFWwindow* glfwWin = GetWindow().GetHandle();

// Agora você tem acesso total às funções nativas do GLFW:
// glfwSetWindowPos(glfwWin, 100, 100);
```