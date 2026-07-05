#include "deoxy/utilities/color.hpp"
#include <cstdint>
#include <deoxy/graphics/opengl/gl_shader.hpp>
#include <deoxy/utilities/math.hpp>
#include <deoxy/utilities/file.hpp>
#include <deoxy/logging/enginelog.hpp>
#include <glad/gl.h>

namespace Deoxy::Graphics::OpenGL {
    GLenum GLShader::ShaderTypeToGLenum(ShaderType type) {
        switch (type) {
            case ShaderType::Vertex: return GL_VERTEX_SHADER;
            case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
            default: DEOXY_INFO("Invalid shader type!"); return GL_VERTEX_SHADER;
        }
    }

    GLShader::GLShader(const std::string& vsPath, const std::string& fsPath) {
        uint32_t vertex = createShader(vsPath, ShaderType::Vertex);
        uint32_t fragment = createShader(fsPath, ShaderType::Fragment);

        m_id = createProgram(vertex, fragment);
        DEOXY_INFO("Created Shader Program at {}", m_id);
    }

    GLShader::~GLShader() {
        if (m_id) {
            glDeleteProgram(m_id);
            m_id = 0;
        }
    }

    void GLShader::Bind() const { glUseProgram(m_id); }
    void GLShader::Unbind() const { glUseProgram(0); }

    template<>
    void GLShader::SetUniform(const std::string& name, const int& value) {
        glUniform1i(getUniformLocation(name), value);
    }

    template<>
    void GLShader::SetUniform(const std::string& name, const float& value) {
        glUniform1f(getUniformLocation(name), value);
    }

    template<>
    void GLShader::SetUniform(const std::string& name, const Math::Vector3& value) {
        glUniform3fv(getUniformLocation(name), 1, Math::GetPointer(value));
    }

    template<>
    void GLShader::SetUniform(const std::string& name, const Math::Vector4& value) {
        glUniform4fv(getUniformLocation(name), 1, Math::GetPointer(value));
    }

    template<>
    void GLShader::SetUniform(const std::string& name, const Math::Matrix4x4& value) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, Math::GetPointer(value));
    }

    uint32_t GLShader::createShader(const std::string& path, ShaderType type) {
        std::string read = Utilities::ReadFileAsString(path);
        if (read.empty()) return 0;

        const char* source = read.c_str();

        GLenum shaderType = ShaderTypeToGLenum(type);
        uint32_t shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        if (!validateShader(shader, type)) {
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    uint32_t GLShader::createProgram(uint32_t vertex, uint32_t fragment) {
        if (vertex == 0 || fragment == 0) return 0;

        uint32_t program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        if (!validateProgram(program)) {
            glDeleteProgram(program);
            return 0;
        }

        return program;
    }

    bool GLShader::validateShader(uint32_t shader, ShaderType type) {
        int logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string infoLog(logLength, '\0');

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
            DEOXY_ERROR(
                "Could not load shader with type {}: {}",
                static_cast<int>(type),
                infoLog
            );
        }

        return success;
    }

    bool GLShader::validateProgram(uint32_t program) {
        int logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::string infoLog(logLength, '\0');

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());
            DEOXY_ERROR(
                "Could not link the shaders: {}",
                infoLog
            );
        }

        return success;
    }

    int GLShader::getUniformLocation(const std::string& name) {
        int location = glGetUniformLocation(m_id, name.c_str());

        if (location == -1) {
            DEOXY_ERROR("Couldn't get uniform location for \"{}\"!", name);
        }

        return location;
    }
}