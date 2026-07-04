# Installation Guide

**Deoxy** uses **CMake** to manage its build system and dependencies. You can integrate it into your project either as a Git submodule or by cloning and building it directly on your system.

---

## Prerequisites

Before starting, ensure you have a compiler with **C++20** support or higher and the following tools installed:

* **CMake** (v3.20+)
* **Git**
* Video drivers supporting **modern OpenGL (3.3+)**

### On Arch Linux / Manjaro:
```bash
sudo pacman -S cmake git base-devel mesa
```

---

## Method 1: Adding as a Git Submodule (Recommended)

The fastest way to use Deoxy in your game is by adding it directly inside your project folder.

In your project's terminal, run:
```bash
git submodule add https://github.com/JJ0o0/DeoxyLib.git external/DeoxyLib
git submodule update --init --recursive
```

### Configuring your CMakeLists.txt

After adding the submodule, simply include Deoxy and link it to your main executable. Your file should look like this:
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyGame LANGUAGES C CXX)

# Force C++20 usage
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Add the Deoxy folder (this will configure GLFW, Glad, ImGui, etc.)
add_subdirectory(external/DeoxyLib)

# 2. Define your executable
add_executable(${PROJECT_NAME} src/main.cpp)

# 3. Link Deoxy to your game
target_link_libraries(${PROJECT_NAME} PRIVATE Deoxy)
```

---

## Method 2: Manual Build and Global Installation

If you prefer to compile the library once and install it on your system to use across multiple projects:

```bash
# Clone the repository
git clone --recursive https://github.com/JJ0o0/DeoxyLib.git
cd DeoxyLib

# Generate build files and compile
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Install to the system (optional)
sudo cmake --install build
```

Then, in the CMakeLists.txt of any of your games, simply use:
```cmake
find_package(Deoxy REQUIRED)
target_link_libraries(MyGame PRIVATE Deoxy::Deoxy)
```