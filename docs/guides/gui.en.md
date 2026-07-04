# UI e GUI

Deoxy comes with native integration for **Dear ImGui**, allowing for the rapid creation of debug interfaces, menus, and tools for your game. System control is divided between the main interface (`GUI`) and its visual customizations (`GUISettings`).

All interface logic must be isolated within the **`OnRenderGUI()`** method of your application's lifecycle.

---

## Customizing the Visuals (`GUISettings`)

The library allows you to modify the behavior and themes of the interface during initialization. You can access these options by calling `GetGUISettings()` inside `OnStart()`:

* **Available Themes (`GUITheme`)**:
    * `Deoxy::GUITheme::Default`: The classic Dear ImGui theme.
    * `Deoxy::GUITheme::Rest`: A modern dark style (based on the *Rest style* by AaronBeardless).
* **Docking Support**: Allows you to freely drag, dock, and organize interface windows across the screen.

### Configuration Example:

```cpp
void OnStart() override {
    // Enables the modern Rest theme
    GetGUISettings().SetTheme(Deoxy::GUITheme::Rest);

    // Enables window docking support
    GetGUISettings().SetDocked(true);
}
```

---

## Drawing Interface Elements (`GUI`)

Within the OnRenderGUI() method, Deoxy automatically initializes and terminates the ImGui frame under the hood. You can use both the standard Dear ImGui API commands and Deoxy's utility functions via GetGUI().

### 1. Drawing Text Directly to the Screen (Overlays)

To draw text (such as FPS counters or debug statuses) floating on the screen without needing to open an ImGui window, use the `DrawText` method. It accepts both `Color` (values from 0.0f to 1.0f) and `Color32` (values from 0 to 255):

```cpp
void OnRenderGUI() override {
    // Draws using Deoxy::Color (Normalized RGBA)
    GetGUI().DrawText(10, 10, Deoxy::Color(1.0f, 1.0f, 1.0f, 1.0f), "FPS: 60");

    // Draws using Deoxy::Color32 (8-bit RGBA)
    GetGUI().DrawText(10, 30, Deoxy::Color32(255, 255, 0, 255), "Debug Mode Active");
}
```

### 2. Positioning Windows with Precision

If you need to create a centered window (such as a Pause or Game Over menu), the `SetNextWindowCentered` method automatically calculates the position based on the current window resolution:

```cpp
void OnRenderGUI() override {
    if (m_gamePaused) {
        // Centers the next ImGui window with a size of 200x150
        GetGUI().SetNextWindowCentered({200, 150});

        ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ImGui::Button("Resume")) m_gamePaused = false;
        if (ImGui::Button("Quit")) Quit();
        ImGui::End();
    }
}
```

!!! note "Note on ImGui"
    Since Deoxy manages the native context, you are free to use any standard `ImGui::` API function (such as `ImGui::Begin`, `ImGui::SliderFloat`, `ImGui::ColorEdit4`) directly within your scope, as long as they are placed inside `OnRenderGUI()`.