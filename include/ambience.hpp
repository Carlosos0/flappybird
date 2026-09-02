/**
 * @file ambience.hpp
 * @brief Declaração da classe ambience, que representa o cenário visual e a gravidade do jogo.
 */
#ifndef AMBIENCE_H
#define AMBIENCE_H

#include <allegro5/allegro.h>
#include "vetor.hpp"

/**
 * @class ambience
 * @brief Classe que representa o cenário visual e a gravidade do jogo.
 * 
 * A classe ambience encapsula a gravidade e o plano de fundo do jogo, 
 * permitindo que diferentes ambientes sejam aplicados ao pássaro/jogo.
 */

class ambience {
private:
    
    vetor gravity; /// Vetor que representa a gravidade no jogo.
    ALLEGRO_BITMAP* background; /// Imagem que representa o plano de fundo do jogo.

public:

    /**
     * @brief Construtor da classe ambience.
     * @param gravity Vetor que representa a gravidade no jogo.
     * @param background Imagem que representa o plano de fundo do jogo.
     */
    ambience(vetor gravity, ALLEGRO_BITMAP* background);
    ~ambience();

    /**
     * @brief Obtém o vetor de gravidade.
     * @return Vetor que representa a gravidade no jogo.
     */
    vetor getGravity() const;

    /**
     * @brief Define o vetor de gravidade.
     * @param gravity Vetor que representa a gravidade no jogo.
     */
    void setGravity(const vetor& gravity);

    /**
     * @brief Obtém a imagem do plano de fundo.
     * @return Imagem que representa o plano de fundo do jogo.
     */
    ALLEGRO_BITMAP* getBackground() const;

    /**
     * @brief Define a imagem do plano de fundo.
     * @param background Imagem que representa o plano de fundo do jogo.
     */
    void setBackground(ALLEGRO_BITMAP* background);
};

#endif