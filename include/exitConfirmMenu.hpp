/**
 * @file exitConfirmMenu.hpp
 * @brief Declaração da classe ExitConfirmMenu.
 */
#ifndef EXITCONFIRMMENU_H
#define EXITCONFIRMMENU_H

#include <allegro5/allegro_font.h>
#include "menu.hpp"

/**
 * @class ExitConfirmMenu
 * @brief Representa o menu de confirmação de saída do jogo.
 * 
 * Herda da classe Menu, e implementa os métodos virtuais para processar eventos, 
 * desenhar o menu e gerenciar o estado do menu.
 */
class ExitConfirmMenu : public Menu {

private:
    ALLEGRO_FONT* fontMenu;     /// Ponteiro para a fonte usada para desenhar o texto no menu.
    MenuState nextState;        /// Estado do menu para o próximo estado após a confirmação ou cancelamento da saída.

    /**
     * @brief Verifica se o mouse está colidindo com um botão.
     * @param mouse_x Coordenada x do mouse.
     * @param mouse_y Coordenada y do mouse.
     * @param button Referência para o botão a ser verificado.
     * @return true se o mouse estiver colidindo com o botão, false caso contrário
     */
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);


public:

    /**
     * @brief Construtor da classe ExitConfirmMenu.
     */
    ExitConfirmMenu();
    ~ExitConfirmMenu();

    /**
     * @brief Processa os eventos do menu, como cliques de mouse e teclas.
     * @param event Referência para o evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha o menu na tela.
     */
    void Draw() override;
    
    /**
     * @brief Retorna a fonte usada para desenhar o texto no menu.
     * @return Ponteiro para a fonte do menu.
     */
    ALLEGRO_FONT* getFont() const { return fontMenu; }

    /**
     * @brief Retorna o próximo estado do menu após a confirmação ou cancelamento da saída.
     * @return Estado do menu para o próximo estado.
     */
    MenuState getNextState() override;

    /**
     * @brief Reseta o estado do menu para o estado inicial.
     */
    void Reset() override;

};
#endif