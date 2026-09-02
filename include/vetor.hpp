/**
 * @file vetor.hpp
 * @brief Representação de um vetor de pares ordenados.
 */
#ifndef VETOR_H
#define VETOR_H

/**
 * @struct vetor
 * @brief Vetor (x, y) com sobrecarga de operações de soma e comparação.
 */
struct vetor {

    float x, y;         /// posições no eixo x e y

    /**
     * @brief Construtor do vetor.
     * @param x Coordenada no eixo x do vetor.
     * @param y Coordenada no eixo y do vetor.
     */
    vetor(float x, float y);

    /**
     * @brief Construtor padrão. Inicializa o vetor com
     * (0, 0).
     */
    vetor();

    /**
     * @brief Sobrecarga do operador de soma para operação com outro vetor.
     * @param otherVector Referência a outro vetor.
     * @return Soma das coordenadas x e de y em um novo vetor.
     */
    vetor operator+ (const vetor& otherVector) const;

    /**
     * @brief Sobrecarga do operador de soma para operação com valores.
     * @param valor Valor a ser somado no vetor.
     * @return (x + valor, y + valor).
     */
    vetor operator+ (float valor) const;

    /**
     * @brief Sobrecarga do operador de comparação para vetores.
     * @param otherVector Referência a outro vetor.
     * @return true se são iguais, false se não.
     */
    bool operator== (const vetor& otherVector) const;
    
};

#endif