/**
 * @file crash.hpp
 * @brief Declaração da classe Crash, que gerencia a detecção de colisões 
 */
#ifndef CRASH_H
#define CRASH_H

#include <memory>
#include <vector>

#include "bird.hpp"
#include "pipeControl.hpp"
#include "floor.hpp"

/**
 * @class Crash
 * @brief Centraliza a lógica de detecção de colisões no jogo.
 * 
 * Verifica colisões utilizando bounding boxes (AABB).
 */
class Crash {

private:
    bool falling;   /// Indica se o pássaro está caindo.    
    bool hitFloor;  /// Indica se o pássaro colidiu com o chão.
    std::shared_ptr<floor> gameFloor; /// Ponteiro inteligente para o objeto floor, que representa o chão do jogo.

public:
    Crash();
    ~Crash();

    /**
     * @brief Verifica se duas caixas delimitadoras (bounding boxes) estão se intersectando.
     * @param x1 Coordenada x da primeira caixa.
     * @param y1 Coordenada y da primeira caixa.
     * @param w1 Largura da primeira caixa.
     * @param h1 Altura da primeira caixa.
     * @param x2 Coordenada x da segunda caixa.
     * @param y2 Coordenada y da segunda caixa.
     * @param w2 Largura da segunda caixa.
     * @param h2 Altura da segunda caixa.
     * @return true se as caixas estiverem se intersectando, false caso contrário.
     */
    bool intersectionBoundingBox(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) const;
    
    /**
     * @brief Verifica se o pássaro colidiu com o chão.
     * @param personagem Referência para o objeto bird que representa o pássaro.
     * @return true se o pássaro colidiu com o chão, false caso contrário.
     */
    bool intersectionFloor(const bird& personagem) const; 
    
    /**
     * @brief Verifica se o pássaro colidiu com um cano.
     * @param personagem Referência para o objeto bird que representa o pássaro.
     * @param pipe Referência para o objeto Pipe que representa o cano.
     * @return true se o pássaro colidiu com o cano, false caso contrário.
     */
    bool intersectionPipe(const bird& personagem, const Pipe& pipe) const;

    /**
     * @brief Obtém o estado de queda do pássaro.
     * @return true se o pássaro estiver caindo, false caso contrário.
     */
    bool getFalling() const;

    /**
     * @brief Define o estado de queda do pássaro.
     * @param falling true para indicar que o pássaro está caindo, false caso contrário.
     */
    void setFalling(bool falling);
    
    /**
     * @brief Obtém o estado de colisão com o chão.
     * @return true se o pássaro colidiu com o chão, false caso contrário.
     */
    bool getHitFloor() const;

    /**
     * @brief Define o estado de colisão com o chão.
     * @param hit true para indicar que o pássaro colidiu com o chão, false caso contrário.
     */
    void setHitFloor(bool hit);

    /**
     * @brief Define o objeto floor que representa o chão do jogo.
     * @param gameFloor Ponteiro inteligente para o objeto floor.
     */
    void setFloor(std::shared_ptr<floor> gameFloor); 

    /**
     * @brief Verifica se o pássaro colidiu com algum cano ou com o chão.
     * @param personagem Referência para o objeto bird que representa o pássaro.
     * @param canos Referência para o objeto pipeControl que gerencia os canos do jogo.
     * @return true se houver colisão, false caso contrário.
     */
    bool checkCrash(bird &personagem, const pipeControl &canos);
};

#endif