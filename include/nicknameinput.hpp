/**
 * @file nicknameinput.hpp
 * @brief Implementação da classe NicknameInput, representando a tela de entrada de nickname do jogador.
 */
#ifndef NICKNAMEINPUT_HPP
#define NICKNAMEINPUT_HPP

#include <allegro5/allegro_font.h>
#include "menu.hpp"

/**
 * @class NicknameInput
 * @brief Classe que representa a tela de entrada de nickname do jogador.
 */
class NicknameInput : public Menu {
private:
    std::string currentNickname;           /// Nickname atual do jogador.
    std::string errorMessage;              /// Mensagem de erro.
    bool showError;                        /// Indica se a mensagem de erro deve ser exibida.
    MenuState nextState;                   /// Próximo estado solicitado.
    ALLEGRO_FONT* font;                    /// Ponteiro para a fonte utilizada na tela.

public:

    /**
     * @brief Construtor da classe NicknameInput.
     * @param font Ponteiro para a fonte utilizada na tela.
     */
    NicknameInput(ALLEGRO_FONT* font);

    /**
     * @brief Processa os eventos da tela de entrada de nickname.
     * @param event Evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha a tela de entrada de nickname.
     */
    void Draw() override;

    /**
     * @return O próximo estado solicitado pela tela.
     */
    MenuState getNextState() override;

    /**
     * @brief Reseta a tela de entrada de nickname ao seu estado inicial.
     */
    void Reset() override;

    /**
     * @brief Define a mensagem de erro a ser exibida na tela.
     * @param message Mensagem de erro a ser exibida.
     */
    void setErrorMessage(const std::string& message);

    /**
     * @return O nickname atual do jogador.
     */
    std::string getNickname() const { return currentNickname; }

    /**
     * @return A mensagem de erro atual.
     */
    std::string getErrorMessage() const { return errorMessage; }

    /**
     * @return Indica se há uma mensagem de erro a ser exibida.
     */
    bool hasError() const { return showError; }

    /**
     * @return Ponteiro para a fonte utilizada na tela.
     */
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif