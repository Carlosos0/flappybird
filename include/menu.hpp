/**
 * @file menu.hpp
 * @brief Declaração da classe pai Menu, com atributos genéricos para os menus do jogo.
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <allegro5/allegro.h>
#include <string>

/**
 * @enum MenuState
 * @brief Enumeração representando os diferentes estados do menu.
 * Cada estado corresponde a uma tela ou ação específica no menu do jogo.
 */
enum class MenuState {
    None,           /// Estado inicial sem ação definida.
    Login,          /// Tela de login redireciona pra loggedmenu
    PlayerRegister, /// Tela de cadastro de novo jogador
    Statistics,     /// Tela de estatísticas (ranking)
    DeletePlayer,   /// Tela de exclusão de jogador
    RestartGame,    /// Tela de reinício do jogo
    GoToMainMenu,   /// Tela de retorno ao menu principal
    Options,        /// Tela de opções
    Logout,         /// Tela de deslogar
    PlayGame,       /// Tela de jogo
    Status,         /// Tela de status do jogador 
    Map,            /// Tela de mapa
    Exit            /// Tela de saída do jogo
};

/**
 * @struct Button
 * @brief Estrutura representando um botão no menu.
 */
struct Button {
    float x, y, width, height;      /// Posição e dimensões do botão na tela.
    // ALLEGRO_BITMAP* image;
    const char* text;               /// Texto exibido no botão.
    MenuState action;               /// Ação do botão representada pelo estado do menu.
};
/**
 * @struct Player
 * @brief Estrutura representando um jogador.
 * Contém informações sobre o nome, apelido, pontuação e estatísticas do jogador.
 */
struct Player {
    std::string name;           /// Nome do jogador.
    std::string nickname;       /// Apelido do jogador, usado para identificação no jogo. 
    int score;                  /// Pontuação do jogador.
    int gamesPlayed;            /// Número de jogos jogados pelo jogador.
    int mapsPlayed[3];          /// Vetor que guarda a quantidade de vezes que o jogador jogou cada mapa.
    std::string dateRegistered; /// Data de cadastro do usuário.
};

/**
 * @class Menu
 * @brief Versão genérica de um Menu (classe pai).
 */
class Menu {
public:
    virtual ~Menu() = default;              /// Destrutor virtual padrão

    /**
     * @brief Processa um evento de entrada (teclado ou mouse).
     * @param event Evento a ser processado.
     */
    virtual void ProcessEvent(const ALLEGRO_EVENT& event) = 0; 

    /**
     * @brief Desenha o estado atual da tela.
     */
    virtual void Draw() = 0;

    /**
     * @return O proximo estado solicitado pela tela.
     */
    virtual MenuState getNextState() = 0; 

    /**
     * @brief Reseta a tela ao seu estado inicial.
     */
    virtual void Reset() = 0;
};

#endif