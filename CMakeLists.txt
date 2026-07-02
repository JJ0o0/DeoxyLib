cmake_minimum_required(VERSION 3.20)
project(DeoxyEngine
    LANGUAGES C CXX
)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Vendor/spdlog)
add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/glm)

add_subdirectory(Deoxy)
add_subdirectory(Sandbox)