# Quick Start

Now that you have Deoxy installed and configured in your project, let's understand how to create the basic structure of a game and how the library manages your application's lifecycle.

---

## The `Deoxy::Application` Class

Unlike libraries where you need to create the `while` loop manually, Deoxy adopts an object-oriented approach. You create a class for your game that inherits from **`Deoxy::Application`** and overrides the lifecycle functions:

```cpp
#include <deoxy/deoxy.hpp>

class MyGame : public Deoxy::Application {
protected:
    void OnStart() override {
        // Executed ONCE at the start of the game
    }

    void OnUpdate(float dt) override {
        // Executed every logical frame (Inputs, Physics, etc.)
    }

    void OnRender() override {
        // Executed every graphical frame (Game Drawing)
    }

    void OnRenderGUI() override {
        // Executed after OnRender (Interface, Text, ImGui)
    }

    void OnQuit() override {
        // Executed immediately before closing
    }
};

int main() {
    MyGame game;
    return game.Run(); // Initializes and runs the main loop
}
```

---

## Understanding the Stages

### 1. Initialization

Use this space to load textures, configure the UI theme, or set window properties that only need to be executed once before the game begins.

```cpp
void OnStart() override {
    GetWindow().SetWindowIcon("assets/icon.png");
    GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);
}
```

### 2. Logic and Real-Time

Here you process player inputs and update the world state. The `dt` (Delta Time) parameter represents the time it took to process the last frame. Always multiply your objects' speed by `dt` to ensure the game runs at the same speed on any monitor (whether 60Hz or 144Hz).

```cpp
void OnUpdate(float dt) override {
    auto input = GetInput();

    // Frame rate independent movement using dt
    if (input.IsKeyDown(Deoxy::KeyCode::W)) player.y += speed * dt;

    // Single-press shortcuts
    if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) m_showSettings = !m_showSettings;
}
```

### 3. Interface Rendering

Deoxy features a dedicated layer to draw text or UI elements over the game, bringing native integration with ImGui. It is perfect for creating menus, debug screens, or inventories.

```cpp
void OnRenderGUI() override {
    // Draws a simple text on the screen using pixel coordinates
    GetGUI().DrawText(10, 10, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), "Hello, Deoxy!");

    // ImGui floating window
    ImGui::Begin("Menu");
    if (ImGui::Button("Quit")) Quit(); // Closes the application cleanly
    ImGui::End();
}
```

---

## Next Step

With the lifecycle understood, add the full code to your `main.cpp` and run your project. In the next module, we will explore in detail how the **Window System** works so we can configure it our own way.