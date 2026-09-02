/**
 * @file gameovermenu.hpp
 * @brief Declaração da classe GameOverMenu, representando o menu de fim de jogo.
 */
#ifndef GAMEOVERMENU_HPP
#define GAMEOVERMENU_HPP

#include <allegro5/allegro_font.h>
#include <vector>
#include "menu.hpp"

/**
 * @class GameOverMenu
 * @brief Menu de fim de jogo, que exibe opções e estatísticas 
 * após o fim do jogo.
 */

class GameOverMenu : public Menu {

private:

    std::vector<Button> buttons;        /// Vetor de botões do menu de fim de jogo.
    MenuState nextState;                /// Estado do menu para o próximo estado após a interação do usuário.
    ALLEGRO_FONT* font;                 /// Ponteiro para a fonte utilizada no menu de fim de jogo.

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
     * @brief Construtor padrão da classe GameOverMenu.
     */
    GameOverMenu();
    ~GameOverMenu();
 
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
     * @brief Reseta o menu.
     */
    void Reset() override;

    /**
     * @brief Obtém o próximo estado do menu.
     * @return O próximo estado do menu.
     */
    MenuState getNextState() override;

    /**
     * @brief Obtém os botões do menu.
     * @return Referência para o vetor de botões.
     */
    const std::vector<Button>& getButtons() const { return buttons; }

    /**
     * @brief Obtém a fonte utilizada no menu.
     * @return Ponteiro para a fonte do menu.
     */
    ALLEGRO_FONT* getFont() const { return font; }

};


#endif