cmake_minimum_required(VERSION 3.20)
project(DeoxyEngine
    LANGUAGES C CXX
)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEOXY_BUILD_SANDBOX "Build Sandbox Project" ON)

add_subdirectory(Vendor)
add_subdirectory(Deoxy)

if(DEOXY_BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif()
