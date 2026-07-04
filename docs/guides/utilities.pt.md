# Utilidades, Logs e Assertions

A Deoxy inclui um conjunto de módulos utilitários para resolver tarefas do dia a dia do desenvolvimento de jogos, como manipulação de vetores, leitura de arquivos de assets, relatórios de logs e validação de segurança via checagens em tempo de compilação/execução.

---

## Sistema Matemático (`Deoxy::Math`)

Para evitar reinventar a roda, a Deoxy integra-se diretamente à biblioteca **GLM** (OpenGL Mathematics). O namespace fornece aliases diretos para vetores e matrizes, além de funções utilitárias essenciais.

### Aliases de Tipos
* **`Deoxy::Math::Vector2`** (`glm::vec2`): Vetor de 2 componentes (ex: posições 2D, tamanhos).
* **`Deoxy::Math::Vector3`** (`glm::vec3`): Vetor de 3 componentes (ex: posições 3D, coordenadas RGB).
* **`Deoxy::Math::Vector4`** (`glm::vec4`): Vetor de 4 componentes.
* **`Deoxy::Math::Matrix4x4`** (`glm::mat4`): Matriz 4x4 (usada para transformações e projeções de câmera).

### Funções Helper e Ponteiros Diretos
Ao interagir com APIs brutas ou componentes de interface (como janelas do ImGui), você frequentemente precisará passar um ponteiro para um array contíguo de floats. A função `GetPointer` resolve isso de forma limpa:

```cpp
Deoxy::Math::Vector3 posicao = {10.0f, 5.0f, 0.0f};

// Interagindo diretamente com o ImGui usando o ponteiro do vetor
ImGui::SliderFloat3("Posição", Deoxy::Math::GetPointer(posicao), -100.0f, 100.0f);

// Funções trigonométricas e arredondamento integrados:
float valorSeno = Deoxy::Math::Sin(3.14159f);
int valorArredondado = Deoxy::Math::Round(4.6f); // Retorna 5
```

---

## Leitura de Arquivos (`Deoxy::Utilities`)

Para carregar códigos de Shaders externos, arquivos de configuração ou scripts de dados, você pode ler o conteúdo de um arquivo de texto diretamente para uma `std::string` com uma única linha:

```cpp
#include <deoxy/utilities/file.hpp>

void OnStart() override {
    // Lê o arquivo inteiro. Se falhar, um aviso automático é enviado ao terminal.
    std::string shaderCodigo = Deoxy::Utilities::ReadFileAsString("assets/shaders/base.glsl");
}
```

---

## Sistema de Logs (`Logging`)

A Deoxy possui um logger robusto baseado em níveis de severidade (`LogLevel`). As mensagens são formatadas nativamente utilizando o padrão do C++20 (`std::format`), permitindo passar variáveis de forma segura e limpa.

Como desenvolvedor da aplicação, você deve utilizar as **Macros de Client** (`APP_...`) para debugar seu jogo:

* `APP_TRACE(...)`: Informações brutas de diagnóstico e fluxo de execução.
* `APP_INFO(...)`: Mensagens informativas gerais (ex: "Sistemas carregados").
* `APP_WARN(...)`: Avisos de comportamento inesperado, mas não fatais.
* `APP_ERROR(...)`: Erros que impediram uma operação de terminar com sucesso.
* `APP_CRITICAL(...)`: Erros catastróficos que antecedem uma queda do sistema.

### Exemplo de Formatação no Terminal:

```cpp
int vida = 80;
std::string nomeItem = "Espada de Ferro";

APP_INFO("O jogador coletou o item: '{}'", nomeItem);
APP_WARN("A vida do jogador está baixa: {} HP!", vida);
```

---

## Validação com Asserts (`APP_ASSERT`)

Para capturar bugs de lógica de forma agressiva durante a fase de desenvolvimento, utilize a macro `APP_ASSERT`.

Se a condição passada for falsa, o sistema dispara uma mensagem de nível `CRITICAL` informando o arquivo exato, a linha do erro, a mensagem personalizada e aborta a execução do programa imediatamente para evitar corrupção de memória.

```cpp
// Verifica se o ponteiro do asset é válido antes de usá-lo
APP_ASSERT(ponteiroTextura != nullptr, "Erro: Tentativa de renderizar uma textura não carregada!");
```

!!! note "Nota de Performance (Zero-Cost)"
    Os Asserts são ativados apenas se a macro de compilação DEOXY_DEBUG estiver definida. Em builds de distribuição final (Release), a macro APP_ASSERT é completamente omitida pelo compilador, garantindo performance máxima para o usuário final.