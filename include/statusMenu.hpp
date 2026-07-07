#ifndef STATUSMENU_HPP
#define STATUSMENU_HPP

#include <allegro5/allegro_font.h>
#include <string>
#include "menu.hpp"

class StatusMenu : public Menu {

    private:
    Button btnVoltar;
    MenuState nextState;
    ALLEGRO_FONT* font;
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);
    
    public:
    StatusMenu(ALLEGRO_DISPLAY* display);
    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    MenuState getNextState() override;
    void Reset() override;
    
    const Button& getBtnVoltar() const { return btnVoltar; }
    ALLEGRO_FONT* getFont() const { return font; }

};

#endif