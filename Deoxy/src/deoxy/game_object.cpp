#include <deoxy/game_object.hpp>

namespace Deoxy {
    GameObject::GameObject(const std::string& name) {
        SetName(name);
    }

    void GameObject::Draw() const {
        if (!m_shader || !m_mesh) return;

        m_shader->Bind();
        m_mesh->Draw();
        m_shader->Unbind();
    }
}