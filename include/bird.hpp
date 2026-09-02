/**
 * @file bird.hpp
 * @brief Declaração da classe bird, que representa o personagem controlado pelo jogador.
 */

#ifndef BIRD_H
#define BIRD_H

#include <memory>
#include <vector>
#include "ambience.hpp"
#include "gameobject.hpp"

/**
 * @class bird
 * @brief personagem controlado pelo jogador.
 * 
 * Herda de gameobject e aplica gravidade ao personagem,
 * limita a velocidade máxima de queda, além de controlar a animação de asas
 * em ciclo de 4 quadros.
 */
class bird : public gameobject {

private:

    bool alive;                 /// Indica se o pássaro está vivo ou não.
    float rotation;             /// Ângulo de rotação do pássaro, usado para simular a inclinação durante o voo.
    vetor jump = vetor(0, -8.52f); /// Vetor que representa a força de salto do pássaro.
    std::vector<ALLEGRO_BITMAP*> frames; /// Vetor que armazena os quadros de animação do pássaro.
    int animationTimer;         /// Temporizador para controlar a velocidade da animação do pássaro.
    int currentFrame;           /// Índice do quadro atual da animação do pássaro.
    std::shared_ptr<ambience> planet; /// Ponteiro inteligente para o objeto ambience, que representa o cenário e gravidade do jogo.

public:

    /**
     * @brief Construtor da classe bird.
     * @param position Posição inicial do pássaro no jogo.
     * @param frames Vetor de imagens que representam os quadros de animação do pássaro.
     * @param width Largura do pássaro.
     * @param heigth Altura do pássaro.
     * @param alive Indica se o pássaro está vivo ou não.
     * @param rotation Ângulo de rotação inicial do pássaro.
     */
    bird(const vetor& position, std::vector<ALLEGRO_BITMAP*> frames, float width, float heigth, bool alive, float rotation);
    ~bird();

    /**
     * @brief Obtém o estado de vida do pássaro.
     * @return true se o pássaro estiver vivo, false caso contrário.
     */
    bool getAlive() const;

    /**
     * @brief Define o estado de vida do pássaro.
     * @param alive true para indicar que o pássaro está vivo, false caso contrário.
     */
    void setAlive(bool alive);

    /**
     * @brief Obtém o ângulo de rotação do pássaro.
     * @return Ângulo de rotação do pássaro.
     */
    float getRotation() const;

    /**
     * @brief Define o ângulo de rotação do pássaro.
     */
    void RotationRange();

    /**
     * @brief Obtém o vetor de salto do pássaro.
     * @return Vetor que representa a força de salto do pássaro.
     */
    vetor getJump() const;

    /**
     * @brief Define o cenário (background e gravidade) do jogo.
     * @param planet Ponteiro inteligente para o objeto ambience.
     */
    void setAmbience(std::shared_ptr<ambience> planet);

    /**
     * @brief Atualiza o estado do pássaro a cada frame.
     */
    void Movement() override;

    /**
     * @brief Executa a ação de salto do pássaro, aplicando a força de salto ao vetor de movimento.
     */
    void JumpAct();

    /**
     * @brief Impede que o pássaro ultrapasse os limites da tela.
     */
    void LimitHeight();
};

#endif