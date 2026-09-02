/**
 * @file register.hpp
 * @brief Declaração da classe Cadastro, responsável pelo menu de registro de jogadores.
 */
#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "menu.hpp"
#include "playermanager.hpp" 

/**
 * @class Cadastro
 * @brief Classe que representa o menu de cadastro de jogadores.
 */
class Cadastro : public Menu {

private:

    bool digitando_nome;            /// Registra se o usuário está digitando.

    std::string nome_atual;         /// Nome atual do player.
    std::string apelido_atual;      /// Apelido do player.
    std::string mensagem;           /// Mensagem de status/erro exibida ao usuário.

    ALLEGRO_DISPLAY* display;       /// Ponteiro para o display (tela) do jogo.
    ALLEGRO_FONT* font;             /// Ponteiro para a fonte utilizada no menu de Cadastro. 
    PlayerManager* playerManager;   /// Gerenciador de jogadores para controle de dados e pontos.

    MenuState nextState;            /// Estado do menu para transição após ações do usuário.

public:

    /**
     * @brief Construtor da classe.
     * @param display Ponteiro para o display do jogo.
     * @param font Ponteiro para a fonte utilizada no menu de Cadastro.
     * @param manager Ponteiro para o gerenciador de jogadores.
     */
    Cadastro(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, PlayerManager* manager);

    /**
     * @brief Processador de eventos no menu de cadastro.
     * @param event Evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha o menu de cadastro na tela.
     */
    void Draw() override;

    /**
     * @brief Reseta o menu de cadastro para seu estado inicial.
     */
    void Reset() override;

    /**
     * @brief Obtém o próximo estado do menu após ações do usuário.
     * @return O próximo estado do menu.
     */
    MenuState getNextState() override;

    /**
     * @return Nome do usuário.
     */
    const std::string& getNomeAtual() const { return nome_atual; }

    /**
     * @return Apelido do usuário atual.
     */
    const std::string& getApelidoAtual() const { return apelido_atual; }

    /**
     * @return Mensagen de status/erro.
     */
    const std::string& getMensagem() const { return mensagem; }

    /**
     * @return true se o usuário está digitando, false se caso contrário.
     */
    bool isDigitandoNome() const { return digitando_nome; }

    /**
     * @return Ponteiro para a fonte utilizada no menu de cadastro.
     */
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif