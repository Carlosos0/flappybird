/**
 * @file pipe.hpp
 * @brief Representação de um cano individual no jogo.
 */
#ifndef PIPE_H
#define PIPE_H

#include "gameobject.hpp"

/**
 * @class Pipe
 * @brief Representa um cano único (tipo inferior por default).
 * Implementa movimento com deslocamento horizontal constante. É utilizada
 * por doublepipes para criar o par de canos superior-inferior e por Crash para calcular
 * as hitboxes.
 */
class Pipe : public gameobject {

private:

    bool bottomType;    /// variável que guarda o tipo do cano (inferior por default). True se for inferior, False se for superior.

public:

    /**
     * @brief Constrói um cano com posição, imagem, tamanho e tipo.
     * @param position Vetor de posição (x, y) do cano.
     * @param image Ponteiro para a imagem do cano.
     * @param width Largura do cano.
     * @param height Altura do cano.
     * @param bottomType Tipo do cano (true = inferior, false = superior).
     */
    Pipe(const vetor& position, ALLEGRO_BITMAP* image, float width, float height, bool bottomType);

    /**
     * @brief destrutor padrão.
     */
    ~Pipe();

    /**
     * @return true se o cano é o cano inferior do par.
     */
    bool IsBottom() const;

    /**
     * @brief desloca o cano horizontalmente na direção do jogador
     */
    void Movement() override;
 
};

#endif