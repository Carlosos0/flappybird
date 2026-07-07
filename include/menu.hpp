#ifndef MENU_HPP
#define MENU_HPP

#include <allegro5/allegro.h>
#include <string>

enum class MenuState {
    None,
    Login, // Tela de login redireciona pra loggedmenu
    PlayerRegister, // Tela de cadastro de novo jogador
    Statistics, // Tela de estatísticas (ranking)
    DeletePlayer, // Tela de exclusão de jogador
    RestartGame, // Tela de reinício do jogo
    GoToMainMenu, 
    Options, // Tela de opções
    Logout, // Tela de deslogar
    PlayGame, // Tela de jogo
    Status, // Tela de status do jogador 
    Map, // Tela de mapa
    Exit
};

struct Button {
    float x, y, width, height;
    const char* text;
    MenuState action; 
};
struct Player {
    std::string name;
    std::string nickname;
    int score;
    int gamesPlayed;
    int mapsPlayed[3];
    std::string dateRegistered;
};
class Menu {
public:
    virtual ~Menu() = default;
    virtual void ProcessEvent(const ALLEGRO_EVENT& event) = 0;
    virtual void Draw() = 0;
    virtual MenuState getNextState() = 0; 
    virtual void Reset() = 0;
};

#endif