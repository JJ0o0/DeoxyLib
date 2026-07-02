add_library(Deoxy STATIC)

target_sources(Deoxy
    PRIVATE
        src/deoxy/application.cpp
        src/deoxy/time.cpp

        src/deoxy/logging/logger.cpp

        src/deoxy/platform/window.cpp

        src/deoxy/input/input.cpp

        ${CMAKE_SOURCE_DIR}/Vendor/stb/src/stb_image.cpp
)

target_include_directories(Deoxy
    PUBLIC
        src/
        include/
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Vendor/stb/include/
)

target_link_libraries(Deoxy
    PUBLIC
        spdlog::spdlog
    PRIVATE
        glfw
        glm::glm
)

target_compile_definitions(Deoxy
    PUBLIC
        $<$<CONFIG:Debug>:DEOXY_DEBUG>
)

target_compile_features(Deoxy PUBLIC cxx_std_20)