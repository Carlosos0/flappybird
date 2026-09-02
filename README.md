# FLAPPY BIRD

Réplica de Flappy Bird em C++ com Allegro 5, com arquitetura orientada a
objetos (polimorfismo), máquina de estados com 14 estados, colisão por
bounding boxes, geração procedural de obstáculos e sistema de
cadastro/ranking de jogadores com persistência em arquivo.

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

