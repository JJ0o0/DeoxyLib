#pragma once

#include <cstdint>
#include <vector>

namespace Deoxy::Graphics::OpenGL {
    class GLIndexBuffer {
        public:
            GLIndexBuffer(const std::vector<uint32_t>& indices);
            ~GLIndexBuffer();

            void Destroy();
            void Bind() const;
            void Unbind() const;

            uint32_t GetIndexCount() { return m_indexCount; }
        private:
            uint32_t m_id = 0;
            uint32_t m_indexCount = 0;
    };
}