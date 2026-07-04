# Sistema de Input

O sistema de entradas da Deoxy permite monitorar o estado do teclado e do mouse em tempo real. Ele lida tanto com estados contínuos (saber se uma tecla está sendo segurada) quanto com eventos de transição de frame (saber se um botão foi pressionado ou solto exatamente neste frame).

---

## Teclado

Dentro de métodos como `OnUpdate(float dt)`, você obtém a instância de input ativa chamando `GetInput()`. A partir dela, você pode passar um `Deoxy::KeyCode` para três verificações:

* **`IsKeyDown(key)`**: Retorna `true` se a tecla estiver sendo **mantida pressionada** (ótimo para movimentação contínua).
* **`WasKeyPressed(key)`**: Retorna `true` **apenas no frame exato em que a tecla foi pressionada** (útil para ações únicas, como abrir menus ou pular).
* **`WasKeyReleased(key)`**: Retorna `true` **apenas no frame exato em que a tecla foi solta**.

### Exemplo de Uso:
```cpp
void OnUpdate(float dt) override {
    auto input = GetInput();

    // Movimentação fluida enquanto segura a tecla
    if (input.IsKeyDown(Deoxy::KeyCode::D)) jogador.MoveRight(dt);
    if (input.IsKeyDown(Deoxy::KeyCode::A)) jogador.MoveLeft(dt);

    // Ação disparada uma única vez por clique
    if (input.WasKeyPressed(Deoxy::KeyCode::Space)) {
        jogador.Jump();
    }
}
```

---

## Cliques do Mouse

O tratamento de botões do mouse segue a mesmíssima lógica do teclado, mas utiliza a enumeração `Deoxy::MouseButton` (como `Left`, `Right`, etc.):

* **`IsMouseButtonDown(button)`**
* **`WasMouseButtonPressed(button)`**
* **`WasMouseButtonReleased(button)`**

### Exemplo de Uso:

```cpp
if (input.WasMouseButtonPressed(Deoxy::MouseButton::Left)) {
    Mundo.DispararProjetil(input.GetMouseX(), input.GetMouseY());
}
```

---

## Posição, Deltas e Scroll do Mouse

A Deoxy atualiza automaticamente a posição absoluta e a variação do movimento do cursor a cada frame, facilitando implementações como câmeras de jogos em primeira pessoa (FPS) ou arrastar de objetos.

### Coordenadas Absolutas

Para obter a posição do mouse em pixels em relação à área de exibição da janela:

```cpp
float mouseX = input.GetMouseX();
float mouseY = input.GetMouseY();
```

### Movimentação Relativa (Delta)

Indica quantos pixels o mouse se moveu **desde o último frame**. Essencial para rotação de câmeras 3D:

```cpp
float deltaX = input.GetMouseDeltaX();
float deltaY = input.GetMouseDeltaY();
```

### Roda do Mouse (Scroll)

Retorna o deslocamento da roda ou touchpad no frame atual tanto na horizontal (geralmente touchpads) quanto na vertical:

```cpp
float scrollX = input.GetScrollX();
float scrollY = input.GetScrollY(); // O scroll padrão de rolagem de página
```