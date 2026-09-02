/**
 * @file doublepipes.hpp
 * @brief Declaração da classe doublepipes, 
 * que representa um par de canos.
 */
#ifndef DOUBLEPIPES_H
#define DOUBLEPIPES_H

#include "pipe.hpp"

/**
 * @class doublepipes
 * @brief Representação de um par de canos (superior e inferior).
 */
class doublepipes {

private:

    Pipe bottom;        /// Cano inferior do par.
    Pipe top;           /// Cano superior do par.
    float gap;          /// Espaço entre os canos.

    /**
     * @brief Calcula a posição do cano superior com base na posição do cano inferior e no espaço entre eles.
     * @param initPipe Referência para o cano inferior.
     * @param gap Espaço entre os canos.
     * @return Vetor representando a posição do cano superior.
     */
    static vetor InvertPipePos(const Pipe& initPipe, float gap); 

public:

    /**
     * @brief Construtor da classe doublepipes.
     * @param initPipe Referência para o cano inferior.
     * @param gap Espaço entre os canos.
     */
    doublepipes(const Pipe& initPipe, float gap);
    ~doublepipes();

    /**
     * @brief Obtém o cano superior do par.
     * @return Referência constante para o cano superior.
     */
    const Pipe& getTop() const;

    /**
     * @brief Obtém o cano inferior do par.
     * @return Referência constante para o cano inferior.
     */
    const Pipe& getBottom() const;

    /**
     * @brief Obtém o espaço entre os canos.
     * @return Valor do espaço entre os canos.
     */
    float getGap() const;
    
    /**
     * @brief Move os canos.
     */
    void DoubleMovement();
    
    /**
     * @brief Verifica se os canos estão fora da tela.
     * @return true se os canos estiverem fora da tela, false caso contrário.
     */
    bool OffScreen();

};

#endif