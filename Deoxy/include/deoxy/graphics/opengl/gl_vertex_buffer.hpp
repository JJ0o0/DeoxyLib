#pragma once

#include "../vertex.hpp"
#include <vector>

namespace Deoxy::Graphics::OpenGL {
    class GLVertexBuffer {
        public:
            GLVertexBuffer(const std::vector<Vertex>& vertices);
            ~GLVertexBuffer();

            void Destroy();
            void Bind() const;
            void Unbind() const;

            uint32_t GetVertexCount() { return m_vertexCount; }
        private:
            uint32_t m_id = 0;
            uint32_t m_vertexCount = 0;
    };
}