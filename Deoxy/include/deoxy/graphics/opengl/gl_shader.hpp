#pragma once

#include <cstdint>
#include <string>

namespace Deoxy::Graphics::OpenGL {
    enum class ShaderType {
        Vertex,
        Fragment
    };

    class GLShader {
        public:
            GLShader(const std::string& vsPath, const std::string& fsPath);
            ~GLShader();

            void Bind() const;
            void Unbind() const;
        private:
            uint32_t m_id = 0;

            uint32_t ShaderTypeToGLenum(ShaderType type);
            uint32_t createShader(const std::string& path, ShaderType type);
            uint32_t createProgram(uint32_t vertex, uint32_t fragment);
            bool validateShader(uint32_t shader, ShaderType type);
            bool validateProgram(uint32_t program);
    };
}