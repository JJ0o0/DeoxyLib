#pragma once

#include "vertex.hpp"
#include "mesh.hpp"
#include <memory>

namespace Deoxy::Graphics {
    inline std::shared_ptr<Mesh> CreateTriangle() {
        std::vector<Vertex> vertices {
            { 
                {0.0f, 0.5f, 0.0f},
            },
            {
                {0.5f, -0.5f, 0.0f},
            },
            {
                {-0.5f, -0.5f, 0.0f},
            }
        };

        std::vector<uint32_t> indices {
            0, 1, 2
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    inline std::shared_ptr<Mesh> CreateQuad() {
        std::vector<Vertex> vertices {
            { 
                {0.5f, 0.5f, 0.0f},
            },
            {
                {0.5f, -0.5f, 0.0f},
            },
            {
                {-0.5f, 0.5f, 0.0f},
            },
            {
                {-0.5f, -0.5f, 0.0f},
            }
        };

        std::vector<uint32_t> indices {
            0, 1, 2,
            1, 2, 3
        };

        return std::make_shared<Mesh>(vertices, indices);
    }
}