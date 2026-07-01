#ifndef MENU_HPP
#define MENU_HPP

#include <allegro5/allegro.h>
#include <string>

enum class MenuState {
    None,
    Game,
    PlayerRegister,
    Statistics,
    DeletePlayer,
    RestartGame,
    GoToMainMenu,
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