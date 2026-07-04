# Rendering and Graphics

Deoxy's graphics module abstracts the modern OpenGL context through the `Deoxy::Graphics::Renderer` class. It manages the viewport state, logical driver initialization, and basic screen clearing operations.

---

## Working with Colors (`Deoxy::Color`)

To manage colors, Deoxy utilizes aliases integrated directly with the **GLM** math library. This means you can perform vector operations and manipulations directly on color structures.

The library provides two main formats:

* **`Deoxy::Color`** (`glm::vec4`): Stores the RGBA channels in normalized floating-point format, where each component ranges from `0.0f` to `1.0f`.
* **`Deoxy::Color32`** (`glm::u8vec4`): Stores the RGBA channels in 8-bit integers, ranging from `0` to `255`.

### Creation and Usage Examples:

```cpp
// Creating a normalized color (RGBA from 0.0f to 1.0f)
Deoxy::Color background = Deoxy::Color(0.1f, 0.1f, 0.13f, 1.0f);

// Creating an 8-bit color (RGBA from 0 to 255)
Deoxy::Color32 gamerGreen = Deoxy::Color32(0, 255, 0, 255);
```

---

## Conversion Helper Functions

If you need to convert color formats to interact with different parts of the engine (such as passing them to the renderer or handling sprite palettes), Deoxy provides two global inline functions:

* `Deoxy::ToNormalizedColor(const Color32& color32)`: Converts from 0-255 to 0.0f-1.0f.
* `Deoxy::ToColor32(const Color& color)`: Converts from 0.0f-1.0f to 0-255 (rounding values properly).

### Usage Examples:

```cpp
Deoxy::Color32 uiColor = Deoxy::Color32(255, 128, 0, 255);

// Converting to the format accepted by the Renderer
GetRenderer().SetClearColor(Deoxy::ToNormalizedColor(uiColor));
```

---

## The Renderer

Within your application, you can access the graphics interface by calling the `GetRenderer()` method.

By default, Deoxy initializes the screen with a subtle dark tone (`0.1f, 0.1f, 0.13f, 1.0f`). You can change and read this color at any time.

### Changing the Background Color (Clear Color)

You can set a new default color, usually during game initialization (`OnStart`):

```cpp
void OnStart() override {
    // Changes the default background to a custom color
    Deoxy::Color myColor = Deoxy::Color(0.2f, 0.3f, 0.3f, 1.0f);
    GetRenderer().SetClearColor(myColor);
}
```

### Reading the Current Color

If you need to read or store the currently configured color:

```cpp
Deoxy::Color currentColor = GetRenderer().GetClearColor();
```

---

## Screen Resizing

The engine automatically handles window resizing under the hood, invoking the `OnResize(width, height)` method to reconfigure the OpenGL viewport whenever the user drags the window borders or toggles the display mode.

---

## What's Next?

Currently, the `Renderer` manages the basic drawing cycle. In future library updates, this section will cover automated geometric primitive drawing and custom Shader loading.