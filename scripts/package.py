import os
import shutil

BUILD_DIR = "build"
DIST_DIR = "dist"
INCLUDE_SRC = "Deoxy/include"
IMGUI_SRC = "Vendor/imgui"
GLM_SRC = "Vendor/glm"

def create_dist():
    print("Creating distribution package...")
    
    if os.path.exists(DIST_DIR):
        shutil.rmtree(DIST_DIR)
    
    os.makedirs(f"{DIST_DIR}/include/Deoxy")
    os.makedirs(f"{DIST_DIR}/include/imgui")
    os.makedirs(f"{DIST_DIR}/include/glm")
    os.makedirs(f"{DIST_DIR}/lib")
    os.makedirs(f"{DIST_DIR}/cmake/Deoxy")
    
    shutil.copytree(INCLUDE_SRC, f"{DIST_DIR}/include/Deoxy", dirs_exist_ok=True)
    shutil.copytree(IMGUI_SRC, f"{DIST_DIR}/include/imgui", dirs_exist_ok=True)
    shutil.copytree(GLM_SRC, f"{DIST_DIR}/include/glm", dirs_exist_ok=True)
    
    shutil.copy(f"{BUILD_DIR}/Deoxy/libDeoxy.a", f"{DIST_DIR}/lib/libDeoxy.a")
    
    print("Generating Deoxy.hpp facade...")
    header_content = """#pragma once

#include "Deoxy/deoxy/deoxy.hpp"
"""
    
    with open(f"{DIST_DIR}/include/Deoxy.hpp", "w") as f:
        f.write(header_content)

    cmake_config = """
set(DEOXY_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")

add_library(Deoxy::Deoxy STATIC IMPORTED)
set_target_properties(Deoxy::Deoxy PROPERTIES
    IMPORTED_LOCATION "${DEOXY_ROOT}/lib/libDeoxy.a"
    INTERFACE_INCLUDE_DIRECTORIES "${DEOXY_ROOT}/include;${DEOXY_ROOT}/include/imgui;${DEOXY_ROOT}/include/glm"
    INTERFACE_LINK_LIBRARIES "imgui;spdlog;GL;glfw;pthread;dl"
)
"""
    with open(f"{DIST_DIR}/cmake/Deoxy/DeoxyConfig.cmake", "w") as f:
        f.write(cmake_config)
    
    print(f"Ready at ./{DIST_DIR}")

if __name__ == "__main__":
    create_dist()