/**
 * @file statusMenu.hpp 
 * @brief Declaração da classe StatusMenu, representação de estatísticas de cada usuário.
 */
#ifndef STATUSMENU_HPP
#define STATUSMENU_HPP

#include <allegro5/allegro_font.h>
#include <string>
#include "menu.hpp"

/**
 * @class StatusMenu
 * @brief Estatísticas do jogador (recorde, partidas por mapa, etc.).
 * Herda de Menu
 */
class StatusMenu : public Menu {

private:
    Button btnVoltar;       /// Botão para retornar ao menu anterior.
    MenuState nextState;    /// Próximo estado solicitado.
    ALLEGRO_FONT* font;     /// Ponteiro para a fonte utilizada.

    /**
     * @brief Verifica se as coordenadas do mouse estão sobre um botão.
     * @param mouse_x Posição X do mouse.
     * @param mouse_y Posição Y do mouse.
     * @param button Botão a ser testado.
     * @return true se o mouse está sobre o botão.
     */
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);
    
public:

    /**
     * @brief Construtor do Menu de status.
     * @param display Ponteiro para a tela de exibição do jogo.
     */
    StatusMenu(ALLEGRO_DISPLAY* display);

    /**
     * @brief Processador de eventos.
     * @param event Evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha o menu na tela.
     */
    void Draw() override;

    /**
     * @brief Reseta o estado do menu para o estado inicial.
     */
    void Reset() override;
    
    /**
     * @return O próximo estado do menu.
     */
    MenuState getNextState() override;
    
    /**
     * @return Referência para o botão de voltar ao menu anterior.
     */
    const Button& getBtnVoltar() const { return btnVoltar; }

    /**
     * @return Fonte utilizada no menu
     */
    ALLEGRO_FONT* getFont() const { return font; }

};

#endif