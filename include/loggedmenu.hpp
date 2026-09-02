/**
 * @file loggedmenu.hpp
 * @brief Declaração da classe LoggedMenu, menu do usuário loggado.
 */
#ifndef LOGGEDMENU_HPP
#define LOGGEDMENU_HPP

#include <allegro5/allegro_font.h>
#include <string>
#include <vector>

#include "menu.hpp"

/**
 * @class LoggedMenu
 * @brief Menu do usuário loggado.
 * Herda da classe Menu.
 */

class LoggedMenu : public Menu {

private:
    ALLEGRO_BITMAP* background;     /// Ponteiro para a imagem de fundo do menu do usuário loggado.
    ALLEGRO_DISPLAY* display;       /// Ponteiro para a tela de exibição do jogo.
    ALLEGRO_FONT* font;             /// Ponteiro para a fonte utilizada no menu do usuário loggado.
    ALLEGRO_FONT* fontNickname;     /// Ponteiro para a fonte utilizada para exibir o nickname do usuário loggado.
    ALLEGRO_FONT* fontMap;          /// Ponteiro para a fonte utilizada para exibir o nome do mapa selecionado.
    ALLEGRO_FONT* fontMenu;         /// Ponteiro para a fonte utilizada para exibir o menu do usuário loggado.

    float backgroundX;              /// Posição x da imagem de fundo do menu do usuário loggado.
    std::vector<Button> buttons;    /// Vetor de botões do menu do usuário loggado.
    MenuState nextState;            /// Estado do menu para o próximo estado após a interação do usuário.
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button); ///< Verifica se o mouse está colidindo com um botão.

public:

    /**
     * @brief Construtor da classe LoggedMenu.
     * @param display Ponteiro para a tela de exibição do jogo.
     */
    LoggedMenu(ALLEGRO_DISPLAY* display);
    ~LoggedMenu();

    /**
     * @brief Processador de eventos.
     * @param event evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha o menu do usuário loggado na tela.
     */
    void Draw() override;

    /**
     * @brief Getter para o ponteiro do background do menu.
     * @return Background do menu.
     */
    ALLEGRO_BITMAP* getBackground() const { return background; }

    /**
     * @brief Getter para o ponteiro da fonte do menu.
     * @return Fonte do menu.
     */
    ALLEGRO_FONT* getFont() const { return fontMenu; }

    /**
     * @brief Getter para o vetor de botões do menu.
     * @return Vetor de botões do menu.
     */
    const std::vector<Button>& getButtons() const { return buttons; }

    /**
     * @brief Getter para a posição x do background do menu.
     * Função necessária para a animação de movimento do background.
     * @return Posição x do background do menu.
     */
    float getBackgroundX() const { return backgroundX; }

    /**
     * @brief Obtém o próximo estado do menu.
     * @return O próximo estado do menu.
     */
    MenuState getNextState() override;

    /**
     * @brief Reseta o menu do usuário loggado para
     * o estado inicial.
     */
    void Reset() override;

    /**
     * @brief Atualiza a posição do background do menu para criar um efeito de movimento.
     */
    void Update();

};

#endif