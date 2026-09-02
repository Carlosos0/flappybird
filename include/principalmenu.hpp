/**
 * @file principalmenu.hpp
 * @brief Declaração da classe PrincipalMenu, que representa o menu principal do jogo.
 */
#ifndef PRINCIPALMENU_HPP
#define PRINCIPALMENU_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <vector>       
 
#include "menu.hpp"      

/**
 * @class PrincipalMenu
 * @brief Representa o menu principal do jogo.
 * Herda de Menu.
 */
class PrincipalMenu : public Menu {
private:
    ALLEGRO_BITMAP* background;         /// Ponteiro para a imagem de fundo do menu.
    ALLEGRO_FONT* fontMenu;             /// Ponteiro para a fonte utilizada nos botões do menu.
    ALLEGRO_FONT* fontTitle;            /// Ponteiro para a fonte utilizada no título do menu.
    ALLEGRO_AUDIO_STREAM* musicMenu;    /// Ponteiro para a música de fundo do menu.
    
    std::vector<Button> buttons;        /// Vetor de botões do menu.
    float backgroundX;                  /// Posição X do fundo do menu para animação de movimento.
    MenuState nextState;                /// Estado do próximo menu a ser exibido após a interação do usuário.

    /**
     * @brief Verifica se houve colisão entre o mouse e um botão.
     * @param mouse_x Posição X do mouse.
     * @param mouse_y Posição Y do mouse.
     * @param button Referência para o botão a ser verificado.
     * @return true se houve colisão, false caso contrário.
     */
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button); 

public:

    /**
     * @brief Construtor da classe PrincipalMenu.
     * @param display Ponteiro para o display do Allegro.
     */
    PrincipalMenu(ALLEGRO_DISPLAY* display);
    ~PrincipalMenu();

    /**
     * @brief Processa um evento de entrada (teclado ou mouse).
     * @param event Evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha o estado atual da tela.
     */
    void Draw() override;

    /**
     * @return O próximo estado solicitado pela tela.
     */
    ALLEGRO_BITMAP* getBackground() const { return background; }

    /**
     * @return Ponteiro para a fonte utilizada nos botões do menu.
     */
    ALLEGRO_FONT* getFont() const { return fontMenu; }

    /**
     * @return Vetor de botões do menu.
     */
    const std::vector<Button>& getButtons() const { return buttons; }

    /**
     * @return Posição X do fundo do menu para animação de movimento.
     */
    float getBackgroundX() const { return backgroundX; }

    /**
     * @return Ponteiro para a fonte utilizada no título do menu.
     */
    ALLEGRO_FONT* getFontTitle() const { return fontTitle; }

    /**
     * @return Ponteiro para a música de fundo do menu.
     */
    MenuState getNextState() override; 

    /**
     * @brief Reinicia o estado do menu, incluindo a posição do fundo e o próximo estado.
     */
    void Reset() override;

    /**
     * @brief Atualiza a posição do fundo do menu para criar um efeito de movimento.
     * A posição do fundo é incrementada a cada chamada, criando um efeito de rolagem contínua.
     */
    void Update();
};

#endif