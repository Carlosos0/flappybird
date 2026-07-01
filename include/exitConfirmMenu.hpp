#ifndef EXITCONFIRMMENU_H
#define EXITCONFIRMMENU_H

#include <allegro5/allegro_font.h>
#include "menu.hpp"

class ExitConfirmMenu : public Menu {

private:
    ALLEGRO_FONT* fontMenu;
    MenuState nextState; 
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);


public:
    ExitConfirmMenu();
    ~ExitConfirmMenu();

    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    ALLEGRO_FONT* getFont() const { return fontMenu; }
    MenuState getNextState() override;
    void Reset() override;

};
#endif