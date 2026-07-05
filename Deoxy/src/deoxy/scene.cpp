#include <deoxy/scene.hpp>
#include <algorithm>

namespace Deoxy {
    GameObject& Scene::CreateGameObject(const std::string& name) {
        m_gameObjects.push_back(std::make_unique<GameObject>(name));

        return *m_gameObjects.back();
    }

    bool Scene::DestroyGameObject(const std::string& name) {
        auto it = std::find_if(
            m_gameObjects.begin(), m_gameObjects.end(),
            [&](const auto& obj) {
                return obj->GetName() == name;
            }
        );

        if (it == m_gameObjects.end()) return false;

        m_gameObjects.erase(it);
        return true;
    }

    GameObject* Scene::FindGameObject(const std::string& name) {
        for (auto& obj : m_gameObjects) {
            if (obj->GetName() != name) continue;

            return obj.get();
        }

        return nullptr;
    }

    std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() { return m_gameObjects; }
    const std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() const { return m_gameObjects; }

    void Scene::Clear() { m_gameObjects.clear(); }
}