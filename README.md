# FLAPPY BIRD

Recriação do jogo Flappy Bird em C++ com a biblioteca gráfica Allegro 5, com arquitetura orientada a objetos baseada em
polimorfismo, máquina de estados, colisão por bounding boxes com hitboxes diferenciadas, geração procedural de obstáculos,
sistema de cadastro/ranking de jogadores e mapas variados.

## Como rodar

```bash
make all
./bin/FlappyBird
```

## Testes

Coberto por testes unitários (framework doctest):

```bash
make test 
```

## Documentação técnica

Documentação completa gerada com Doxygen (arquitetura, classes, métodos):
**[carlosos0.github.io/flappybird](https://carlosos0.github.io/flappybird/)**

Para gerar localmente:
```bash
doxygen Doxyfile
```
Abre em `docs/html/index.html`.

## Tecnologias Utilizadas no projeto:

* **C++14**
* **Allegro 5**
* **Doxygen**
* **doctest**

