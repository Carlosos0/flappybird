/**
 * @file pipeControl.hpp
 * @brief Declaração da classe pipeControl.hpp, responsável pela geração
 * procedural e pelo ciclo de vida dos canos.
 */
#ifndef PIPECONTROL_H
#define PIPECONTROL_H

#include <algorithm>
#include <memory>
#include <vector>

#include "doublepipes.hpp"

/**
 * @class pipeControl
 * @brief Gerencia a coleção de pares de canos em cena (spawn, movimento e remoção).
 *
 * Sorteia a altura de cada novo par de canos dentro de limites configurados (RandHCalculator),
 * decide o momento de gerar um novo par com base na distância do último
 * par gerado (WhenSpawn), atualiza a posição de todos os pares a cada
 * frame (UpdatePos) e remove os pares que já saíram da tela (DeletePipes).
 */

class pipeControl {

protected:

    std::vector<std::unique_ptr<doublepipes>> pipeHouse;    /// Vetor onde os pares de canos são alocados.
    ALLEGRO_BITMAP* pipeImg;                                /// Ponteiro para a imagem do cano. 

    float pipeGap;                  /// Distância entre o cano superior e inferior de um par.
    float pipeDistance;             /// Distância entre os pares de canos.

    float pipeWidth;                /// Largura do cano.
    float pipeHeight;               /// Altura do cano.

    float SCREEN_W;                 /// Dimensão da largura (width) da tela.
    float SCREEN_H;                 /// Dimensão da altura (height) da tela.

public:

    /**
     * @brief Construtor do controlador.
     * @param pipeImg Imagem dos canos.
     * @param pipeGap Espaço entre canos, por onde o pássaro passa.
     * @param pipeDistance Distância entre os pares de canos.
     * @param pipeWidht Largura do cano.
     * @param pipeHeight Altura do cano.
     * @param SCREEN_W Largura da tela.
     * @param SCREEN_H Altura da tela.
     */
    pipeControl(ALLEGRO_BITMAP* pipeImg, float pipeGap, float pipeDistance, 
                float pipeWidht, float pipeHeight,        
                float SCREEN_W, float SCREEN_H);
        
    ~pipeControl();

    /**
     * @return vetor de par de canos (inferior e superior).
     */
    const std::vector<std::unique_ptr<doublepipes>>& getPipeHouse() const;

    /**
     * @brief Sorteia uma posição (eixo y) para o próximo cano inferior do par.
     * @return Altura aleatória dentro do limite estabelecido.
     */
    int RandHCalculator();

    /**
     * @brief Verifica se outro par de canos pode ser gerado, com base na posição
     * (eixo x) do último par de canos gerado.
     * @return true se um novo par de canos deve ser gerado nesse frame.
     */
    bool WhenSpawn();

    /**
     * @brief Função que gera um novo par de canos.
     * Atua junto com WhenSpawn().
     */
    void PipeGenerator();

    /**
     * @brief Atualiza a posição (eixo x) dos pares de canos na tela.
     */
    void UpdatePos();

    /**
     * @brief Remove do vetor de par de canos aqueles que saíram da tela.
     */
    void DeletePipes();
};

#endif