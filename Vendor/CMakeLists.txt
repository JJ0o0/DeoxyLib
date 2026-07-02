cmake_minimum_required(VERSION 3.20)
project(VendorDependencies LANGUAGES CXX)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(spdlog)

set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp

    imgui/misc/cpp/imgui_stdlib.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC 
    imgui
    imgui/backends
    imgui/misc
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)