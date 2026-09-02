/**
 * @file gameobject.hpp
 * @brief Declaração da classe gameobject, representação de um objeto no jogo.
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <allegro5/allegro.h>

#include "vetor.hpp"

/**
 * @class gameobject
 * @brief Representa um objeto no jogo, com posição, imagem, dimensões e velocidade de movimento.
 */
class gameobject {

protected:

    vetor position;         /// Posição do objeto no jogo.
    ALLEGRO_BITMAP* image;  /// Ponteiro para a imagem do objeto.
    float width, height;    /// Dimensões do objeto (largura e altura).
    vetor move_speed;       /// Velocidade de movimento do objeto.

public:

    /**
     * @brief Construtor padrão da classe gameobject.
     */
    gameobject();
    virtual ~gameobject();

    /**
     * @brief Método virtual puro para definir o comportamento de movimento do objeto.
     * Este método deve ser implementado pelas classes derivadas para definir como o objeto
     * se move no jogo.
     */
    virtual void Movement() = 0; 

    /**
     * @brief Obtém a imagem do objeto.
     * @return Ponteiro para a imagem do objeto.
     */
    ALLEGRO_BITMAP* getImage() const;

    /**
     * @brief Define a imagem do objeto.
     * @param image Ponteiro para a nova imagem do objeto.
     */
    void setImage(ALLEGRO_BITMAP* image);
    
    /**
     * @brief Obtém a posição do objeto.
     * @return Vetor representando a posição do objeto.
     */
    vetor getPosition() const;

    /**
     * @brief Define a posição do objeto.
     * @param position Vetor representando a nova posição do objeto.
     */
    void setPosition(const vetor& position);

    /**
     * @brief Obtém a largura do objeto.
     * @return Largura do objeto.
     */
    float getWidth() const;

    /**
     * @brief Define a largura do objeto.
     * @param width Nova largura do objeto.
     */
    void setWidth(float width);

    /**
     * @brief Obtém a altura do objeto.
     * @return Altura do objeto.
     */
    float getHeight() const;

    /**
     * @brief Define a altura do objeto.
     * @param height Nova altura do objeto.
     */
    void setHeight(float height);

    /**
     * @brief Obtém a velocidade de movimento do objeto.
     * @return Vetor representando a velocidade de movimento do objeto.
     */
    vetor getMS() const;

    /**
     * @brief Define a velocidade de movimento do objeto.
     * @param move_speed Vetor representando a nova velocidade de movimento do objeto.
     */
    void setMS(const vetor& move_speed);

};

#endif