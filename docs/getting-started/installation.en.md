# Installation Guide

**Deoxy** uses **CMake** to manage its build and dependencies. You can integrate it into your project either as a Git submodule or by cloning and building it directly on your system.

---

## Prerequisites

Before starting, ensure you have a compiler with support for **C++20** or higher and the following tools installed:

* **CMake** (v3.20+)
* **Git**
* Graphics drivers with support for **modern OpenGL (3.3+)**

### On Arch Linux / Manjaro:
```bash
sudo pacman -S cmake git base-devel mesa
```

## Method 1: Adding as a Git Submodule (Recommended)

The fastest way to use Deoxy in your game is by adding it directly inside your project's folder.

In your project terminal, run:
```bash
git submodule add https://github.com/JJ0o0/DeoxyLib.git external/DeoxyLib
git submodule update --init --recursive
```

### Configuring your CMakeLists.txt

After adding the submodule, simply call Deoxy and link it to your main executable. Your file should look similar to this:

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyGame LANGUAGES C CXX)

# Enforce C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Add the Deoxy folder (this will configure GLFW, Glad, ImGui, etc.)
add_subdirectory(external/DeoxyLib)

# 2. Define your executable
add_executable(${PROJECT_NAME} src/main.cpp)

# 3. Link Deoxy to your game
target_link_libraries(${PROJECT_NAME} PRIVATE Deoxy)
```

## Method 2: Consumption via SDK (Pre-built)

If you do not want to compile Deoxy's source code every time, you can download the compiled version directly from our [Releases](https://github.com/JJ0o0/DeoxyLib/releases) page.

1. Download the `Deoxy-SDK.zip` file from the latest release.
2. Unpack it into your project's `libs/` folder.
3. In your `CMakeLists.txt`, point to the SDK folder:

```cmake
# Add the path where you placed the unpacked folder.
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/Deoxy")

find_package(Deoxy REQUIRED)

add_executable(MyGame src/main.cpp)
target_link_libraries(MyGame PRIVATE Deoxy::Deoxy)
```

---

## Testing

To test if everything is working correctly, copy and paste this example code:

```cpp
#include <Deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {}

        void OnUpdate(float dt) override {
            auto input = GetInput();

            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) Quit();
        }

        void OnRender() override {}

        void OnRenderGUI() override {}

        void OnQuit() override {}
};

int main() {
    Game game;
    return game.Run();
}
```