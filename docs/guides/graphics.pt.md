# Renderização e Gráficos

O módulo de gráficos da Deoxy abstrai o contexto do OpenGL moderno por meio da classe `Deoxy::Graphics::Renderer`. Ele gerencia o estado da viewport, a inicialização dos drivers lógicos e as operações básicas de limpeza de tela.

---

## Trabalhando com Cores (`Deoxy::Color`)

Para gerenciar cores, a Deoxy utiliza aliases integrados diretamente com a biblioteca matemática **GLM**. Isso significa que você pode realizar operações de vetores e manipulações diretamente nas estruturas de cor.

A biblioteca fornece dois formatos principais:

* **`Deoxy::Color`** (`glm::vec4`): Armazena os canais RGBA em ponto flutuante normalizado, onde cada componente varia de `0.0f` a `1.0f`.
* **`Deoxy::Color32`** (`glm::u8vec4`): Armazena os canais RGBA em inteiros de 8 bits, variando de `0` a `255`.

### Exemplos de Criação e Uso:

```cpp
// Criando uma cor normalizada (RGBA de 0.0f a 1.0f)
Deoxy::Color fundo = Deoxy::Color(0.1f, 0.1f, 0.13f, 1.0f);

// Criando uma cor de 8 bits (RGBA de 0 a 255)
Deoxy::Color32 verdeGamer = Deoxy::Color32(0, 255, 0, 255);
```

## Funções Helper de Conversão

Se você precisar converter formatos de cor para interagir com diferentes partes da engine (como mandar para o renderizador ou tratar paletas de sprites), a Deoxy fornece duas funções inline globais:

* `Deoxy::ToNormalizedColor(const Color32& color32)`: Converte de 0-255 para 0.0f-1.0f.
* `Deoxy::ToColor32(const Color& color)`: Converte de 0.0f-1.0f para 0-255 (arredondando os valores corretamente).

### Exemplos de Uso:

```cpp
Deoxy::Color32 corInterface = Deoxy::Color32(255, 128, 0, 255);

// Convertendo para o formato aceito pelo Renderer
GetRenderer().SetClearColor(Deoxy::ToNormalizedColor(corInterface));
```

---

## O Renderizador

Dentro da sua aplicação, você pode acessar a interface gráfica chamando o método `GetRenderer()`.

Por padrão, a Deoxy inicializa a tela com um tom escuro sutil (`0.1f, 0.1f, 0.13f, 1.0f`). Você pode alterar e ler essa cor a qualquer momento.

### Alterando a cor de fundo (Clear Color)

Você pode definir uma nova cor padrão, geralmente na inicialização do jogo (`OnStart`):

```cpp
void OnStart() override {
    // Altera o fundo padrão para uma cor personalizada
    Deoxy::Color minhaCor = Deoxy::Color(0.2f, 0.3f, 0.3f, 1.0f);
    GetRenderer().SetClearColor(minhaCor);
}
```

### Lendo a cor atual

Se precisar ler ou armazenar a cor configurada no momento:

```cpp
Deoxy::Color corAtual = GetRenderer().GetClearColor();
```

---

## Redimensionamento da Tela

A engine lida com a mudança de tamanho da janela automaticamente debaixo dos panos, invocando o método `OnResize(width, height)` para reconfigurar a viewport do OpenGL sempre que o usuário arrasta as bordas da janela ou alterna o modo de exibição.

---

## O que vem por aí?

Atualmente, o `Renderer` gerencia o ciclo básico de desenho. Nos próximos updates da biblioteca, esta seção cobrirá o desenho automatizado de primitivos geométricos e o carregamento de Shaders customizados.