# Utilities, Logs & Assertions

Deoxy includes a set of utility modules to handle day-to-day game development tasks, such as vector manipulation, asset file reading, log reporting, and safety validation via compile-time/runtime checks.

---

## Math System (`Deoxy::Math`)

To avoid reinventing the wheel, Deoxy integrates directly with the **GLM** (OpenGL Mathematics) library. The namespace provides direct aliases for vectors and matrices, alongside essential utility functions.

### Type Aliases
* **`Deoxy::Math::Vector2`** (`glm::vec2`): 2-component vector (e.g., 2D positions, sizes).
* **`Deoxy::Math::Vector3`** (`glm::vec3`): 3-component vector (e.g., 3D positions, RGB coordinates).
* **`Deoxy::Math::Vector4`** (`glm::vec4`): 4-component vector.
* **`Deoxy::Math::Matrix4x4`** (`glm::mat4`): 4x4 matrix (used for camera transformations and projections).

### Helper Functions and Direct Pointers
When interacting with raw APIs or user interface components (like ImGui windows), you will frequently need to pass a pointer to a contiguous array of floats. The `GetPointer` function resolves this cleanly:

```cpp
Deoxy::Math::Vector3 position = {10.0f, 5.0f, 0.0f};

// Interacting directly with ImGui using the vector pointer
ImGui::SliderFloat3("Position", Deoxy::Math::GetPointer(position), -100.0f, 100.0f);

// Integrated trigonometric and rounding functions:
float sineValue = Deoxy::Math::Sin(3.14159f);
int roundedValue = Deoxy::Math::Round(4.6f); // Returns 5
```

---

## File Reading (`Deoxy::Utilities`)

To load external Shader source codes, configuration files, or data scripts, you can read the contents of a text file directly into a `std::string` with a single line of code:

```cpp
#include <deoxy/utilities/file.hpp>

void OnStart() override {
    // Reads the entire file. If it fails, an automatic warning is printed to the terminal.
    std::string shaderCode = Deoxy::Utilities::ReadFileAsString("assets/shaders/base.glsl");
}
```

---

## Logging System (`Logging`)

Deoxy features a robust logger based on severity levels (`LogLevel`). Messages are formatted natively using the C++20 standard (`std::format`), allowing you to pass variables safely and cleanly.

As the application developer, you should use the **Client Macros** (`APP_...`) to debug your game:

* `APP_TRACE(...)`: Raw diagnostic information and execution flow.
* `APP_INFO(...)`: General informative messages (e.g., "Systems successfully initialized").
* `APP_WARN(...)`: Warnings of unexpected but non-fatal behavior.
* `APP_ERROR(...)`: Errors that prevented an operation from completing successfully.
* `APP_CRITICAL(...)`: Catastrophic errors leading up to a system crash.

### Terminal Formatting Example:

```cpp
int health = 80;
std::string itemName = "Iron Sword";

APP_INFO("The player collected the item: '{}'", itemName);
APP_WARN("Player health is low: {} HP!", health);
```

---

## Validation with Asserts (`APP_ASSERT`)

To aggressively catch logic bugs during the development phase, utilize the `APP_ASSERT` macro.

If the passed condition evaluates to false, the system triggers a `CRITICAL` level log message detailing the exact file, line number, and custom error message, immediately aborting program execution to avoid memory corruption.

```cpp
// Verifies if the asset pointer is valid before using it
APP_ASSERT(texturePointer != nullptr, "Error: Attempted to render an unloaded texture!");
```

!!! note "Performance Note (Zero-Cost)"
    Asserts are only enabled if the `DEOXY_DEBUG` compilation macro is defined. In final distribution builds (Release), the `APP_ASSERT` macro is completely omitted by the compiler, ensuring maximum performance for the end user.