# Input System

Deoxy's input system allows you to monitor keyboard and mouse states in real-time. It handles both continuous states (knowing if a key is being held down) and frame-transition events (knowing if a button was pressed or released exactly during the current frame).

---

## Keyboard

Within methods like `OnUpdate(float dt)`, you obtain the active input instance by calling `GetInput()`. From there, you can pass a `Deoxy::KeyCode` to perform three types of checks:

* **`IsKeyDown(key)`**: Returns `true` if the key is **currently being held down** (perfect for continuous movement).
* **`WasKeyPressed(key)`**: Returns `true` **only in the exact frame the key was pressed** (useful for single actions, such as opening menus or jumping).
* **`WasKeyReleased(key)`**: Returns `true` **only in the exact frame the key was released**.

### Usage Example:
```cpp
void OnUpdate(float dt) override {
    auto input = GetInput();

    // Smooth movement while holding down the key
    if (input.IsKeyDown(Deoxy::KeyCode::D)) player.MoveRight(dt);
    if (input.IsKeyDown(Deoxy::KeyCode::A)) player.MoveLeft(dt);

    // Action triggered once per key press
    if (input.WasKeyPressed(Deoxy::KeyCode::Space)) {
        player.Jump();
    }
}
```

---

## Mouse Clicks

Handling mouse buttons follows the exact same logic as the keyboard, but utilizes the `Deoxy::MouseButton` enumeration (such as `Left`, `Right`, etc.):

* **`IsMouseButtonDown(button)`**
* **`WasMouseButtonPressed(button)`**
* **`WasMouseButtonReleased(button)`**

### Usage Example:

```cpp
if (input.WasMouseButtonPressed(Deoxy::MouseButton::Left)) {
    World.FireProjectile(input.GetMouseX(), input.GetMouseY());
}
```

---

## Mouse Position, Deltas, and Scroll

Deoxy automatically updates the absolute position and cursor movement variation every frame, making implementations like first-person shooter (FPS) cameras or dragging objects straightforward.

### Absolute Coordinates

To get the mouse position in pixels relative to the window's viewport area:

```cpp
float mouseX = input.GetMouseX();
float mouseY = input.GetMouseY();
```

### Relative Movement (Delta)

Indicates how many pixels the mouse has moved **since the last frame**. This is essential for 3D camera rotation:

```cpp
float deltaX = input.GetMouseDeltaX();
float deltaY = input.GetMouseDeltaY();
```

### Mouse Wheel (Scroll)

Returns the wheel or touchpad offset in the current frame for both horizontal (usually touchpads) and vertical directions:

```cpp
float scrollX = input.GetScrollX();
float scrollY = input.GetScrollY(); // Standard page scrolling
```