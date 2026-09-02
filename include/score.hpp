/**
 * @file score.hpp
 * @brief Implementação da classe score, representado a pontuação do jogador.
 */
#ifndef SCORE_HPP
#define SCORE_HPP

#include "bird.hpp"
#include "doublepipes.hpp"
#include "pipeControl.hpp"

/**
 * @class score
 * @brief Classe que implementa a pontuação do jogador conforme ele atravessa canos.
 */
class score {
private:

    int currentScore;       /// Pontuação atual do jogador.
    bool canScore;          /// Variável que é true se o jogador está apto a pontuar.

public:

    /**
     * @brief Construtor padrão.
     */
    score();

    /**
     * @brief Destrutor padrão.
     */
    ~score();
    
    /**
     * @return A pontuação atual do jogador.
     */
    int getCurrentScore() const;

    /**
     * @brief Define diretamente a pontuação atual.
     * @param score Nova pontuação.
     */
    void setCurrentScore(int score);

    /**
     * @brief Reseta a pontuação para 0 ao iniciar uma nova partida.
     */
    void resetScore();
    
    /**
     * @brief Verifica se o jogador passou entre dois canos e incrementa a pontuação 
     * uma vez por passagem.
     * @param gameBird Referência ao pássaro do jogo.
     * @param pipes Controlador de canos, com os pares em cena.
     */
    void updateScore(const bird& gameBird, const pipeControl& pipes);
};

#endif