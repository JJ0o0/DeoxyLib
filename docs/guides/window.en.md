# Window System

The management of the main window in Deoxy is handled by the `Deoxy::Platform::Window` class. You can interact with it either by defining its initial properties or by modifying its state in real-time during game execution.

---

## Initial Configuration

By default, Deoxy initializes an `800x600` windowed mode screen with VSync enabled. However, if your constructor inherits from `Deoxy::Application`, you can customize this state by passing a `WindowProperties` struct.

The structure accepts the following fields:

* `Title` (std::string): The title of the window.
* `Icon` (std::string): Path to the `.png` image.
* `Width` / `Height` (uint32_t): Resolution in pixels.
* `Mode` (`WindowMode`): Screen display state (`Windowed`, `BorderlessFullscreen`, or `ExclusiveFullscreen`).
* `VSync` (bool): Enables or disables vertical synchronization.

---

## Real-Time Manipulation

Within any method of your application's lifecycle (such as `OnStart` or `OnUpdate`), you can access the active window instance using the `GetWindow()` method.

### Changing Basic Properties

```cpp
void OnStart() override {
    // Sets the title dynamically
    GetWindow().SetWindowTitle("Deoxy Engine - Creation Edition");

    // Resizes the window
    GetWindow().SetWindowSize(1280, 720);

    // Changes the taskbar icon
    GetWindow().SetWindowIcon("assets/textures/icon.png");
}
```

### Fullscreen and VSync Control

Deoxy simplifies switching display modes through toggle functions, which are ideal for mapping to keyboard shortcuts within `OnUpdate`:

```cpp
void OnUpdate(float dt) override {
    auto input = GetInput();

    // Toggles between Windowed and Exclusive Fullscreen Mode with F11
    if (input.WasKeyPressed(Deoxy::KeyCode::F11)) {
        GetWindow().ToggleFullscreen();
    }

    // Turns VSync On/Off with the V key
    if (input.WasKeyPressed(Deoxy::KeyCode::V)) {
        GetWindow().ToggleVsync();
    }
}
```

!!! note "Alternative"
    For direct control without toggling, you can also use:

    * `GetWindow().SetWindowMode(Deoxy::Platform::WindowMode::BorderlessFullscreen);`
    * `GetWindow().SetWindowVsync(false);`

### Reading Window Properties

If you need to check the current state of the window (for instance, to display the status on your graphical user interface), you can access the internal properties with `GetProperties()`:

```cpp 
void OnRenderGUI() override {
    auto& props = GetWindow().GetProperties();

    GetGUI().DrawText(10, 50, 
        Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), 
        std::format("Current Resolution: {}x{}", props.Width, props.Height)
    );
}
```

---

## Advanced Features

If you need to extend the library or achieve something very specific that relies directly on the GLFW API, Deoxy provides direct access to the native window pointer via the `GetHandle()` method:

```cpp
GLFWwindow* glfwWin = GetWindow().GetHandle();

// Now you have full access to native GLFW functions:
// glfwSetWindowPos(glfwWin, 100, 100);
```