# Guia de Instalação

A **Deoxy** utiliza o **CMake** para gerenciar seu build e suas dependências. Você pode integrá-la ao seu projeto tanto como um submódulo Git quanto clonando e buildando diretamente no seu sistema.

---

## Pré-requisitos

Antes de começar, certifique-se de ter um compilador com suporte a **C++20** ou superior e as seguintes ferramentas instaladas:

* **CMake** (v3.20+)
* **Git**
* Drivers de vídeo com suporte a **OpenGL moderno (3.3+)**

### No Arch Linux / Manjaro:
```bash
sudo pacman -S cmake git base-devel mesa
```

## Método 1: Adicionando como Submódulo Git (Recomendado)

A forma mais rápida de usar a Deoxy no seu jogo é adicionando-a diretamente dentro da pasta do seu projeto.

No terminal do seu projeto, rode:
```bash
git submodule add https://github.com/JJ0o0/DeoxyLib.git external/DeoxyLib
git submodule update --init --recursive
```

### Configurando o seu CMakeLists.txt

Depois de adicionar o submódulo, basta chamar a Deoxy e linká-la no seu executável principal. Seu arquivo deve ficar parecido com isto:
```cmake

cmake_minimum_required(VERSION 3.20)
project(MeuJogo LANGUAGES C CXX)

# Força o uso do C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Adiciona a pasta da Deoxy (isso vai configurar o GLFW, Glad, ImGui, etc.)
add_subdirectory(external/DeoxyLib)

# 2. Define o seu executável
add_executable(${PROJECT_NAME} src/main.cpp)

# 3. Linka a Deoxy ao seu jogo
target_link_libraries(${PROJECT_NAME} PRIVATE Deoxy)
```

## Método 2: Consumo via SDK (Pre-built)

Se você não quer compilar o código-fonte da Deoxy toda vez, você pode baixar a versão compilada diretamente da nossa página de [Releases](https://github.com/JJ0o0/DeoxyLib/releases).

1. Baixe o arquivo `Deoxy-SDK.zip` da última release.
2. Descompacte na pasta `libs/` do seu projeto.
3. No seu `CMakeLists.txt`, aponte para a pasta da SDK:

```cmake
# Adicione o caminho onde você colocou a pasta descompactada.
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/Deoxy")

find_package(Deoxy REQUIRED)

add_executable(MeuJogo src/main.cpp)
target_link_libraries(MeuJogo PRIVATE Deoxy::Deoxy)
```

---

## Testando

Para testar se está tudo funcionando corretamente, copie e cole esse código de exemplo:

```cpp
#include <Deoxy.hpp>

class Game : public Deoxy::Application {
    protected:
        void OnStart() override {}

        void OnUpdate(float dt) override {
            auto input = GetInput();

            if (input.WasKeyPressed(Deoxy::KeyCode::Escape)) Quit();
        }

        void OnRender() override {}

        void OnRenderGUI() override {}

        void OnQuit() override {}
};

int main() {
    Game game;
    return game.Run();
}
```