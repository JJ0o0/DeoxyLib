#pragma once

#include "game_object.hpp"
#include <vector>

namespace Deoxy {
    class Scene {
        public:
            GameObject& CreateGameObject(const std::string& name);
            bool DestroyGameObject(const std::string& name);

            GameObject* FindGameObject(const std::string& name);
            std::vector<std::unique_ptr<GameObject>>& GetGameObjects();
            const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

            void Clear();
        private:
            std::vector<std::unique_ptr<GameObject>> m_gameObjects = {};
    };
}