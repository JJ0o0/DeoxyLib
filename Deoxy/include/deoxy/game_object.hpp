#pragma once

#include "graphics/mesh.hpp"
#include "graphics/opengl/gl_shader.hpp"
#include <memory>

namespace Deoxy {
    class GameObject {
        public:
            GameObject(const std::string& name);
            ~GameObject() = default;

            void Draw() const;
            void Destroy();

            void SetName(const std::string& name) { m_name = name; }
            void SetMesh(const std::shared_ptr<Graphics::Mesh>& mesh) { m_mesh = mesh; }
            void SetShader(const std::shared_ptr<Graphics::OpenGL::GLShader>& shader) { m_shader = shader; }

            void SetMesh(const std::vector<Graphics::Vertex>& vertices, const std::vector<uint32_t>& indices) { 
                m_mesh = std::make_shared<Graphics::Mesh>(vertices, indices); 
            }

            void SetShader(const std::string& vsPath, const std::string& fsPath) { 
                m_shader = std::make_shared<Graphics::OpenGL::GLShader>(vsPath, fsPath); 
            }

            const std::string& GetName() const { return m_name; }
            const std::shared_ptr<Graphics::Mesh>& GetMesh() const { return m_mesh; }
            const std::shared_ptr<Graphics::OpenGL::GLShader>& GetShader() const { return m_shader; }
        private:
            std::string m_name = "GameObject";
            std::shared_ptr<Graphics::Mesh> m_mesh = nullptr;
            std::shared_ptr<Graphics::OpenGL::GLShader> m_shader = nullptr;
    };
}