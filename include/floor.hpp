/**
 * @file floor.hpp
 * @brief Declaração da classe floor, representação do chão do jogo.
 */
#ifndef FLOOR_H
#define FLOOR_H

#include "gameobject.hpp"
#include "vetor.hpp"

/**
 * @class floor
 * @brief Chão do jogo, com função de movimento horizontal pra simular deslocamento do cenário.
 */
class floor: public gameobject {
    private:
    float backgroundX;      /// Posição no eixo X do fundo do chão.

    public:

    /**
     * @brief Construtor da classe floor.
     * @param position Posição inicial do chão no jogo.
     * @param image Imagem do chão.
     * @param width Largura do chão.
     * @param height Altura do chão.
     */
    floor(const vetor& position, ALLEGRO_BITMAP* image, float width, float height);
    ~floor();

    /**
     * @brief Move o chão horizontalmente para simular o deslocamento do cenário.
     */
    void Movement() override;

    /**
     * @brief Atualiza o estado do chão.
     */
    void Update();

    /**
     * @brief Obtém a posição no eixo X do fundo do chão.
     * @return Posição no eixo X do fundo do chão.
     */
    float getBackgroundX() const { return backgroundX; }
};

#endif