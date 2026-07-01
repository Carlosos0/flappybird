#ifndef GAMEOVERMENU_HPP
#define GAMEOVERMENU_HPP

#include <allegro5/allegro_font.h>
#include <vector>
#include "menu.hpp"

class GameOverMenu : public Menu {

private:

std::vector<Button> buttons;

    MenuState nextState;
    ALLEGRO_FONT* font;
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);

public:

 GameOverMenu();
 ~GameOverMenu();
 
    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    void Reset() override;

    MenuState getNextState() override;
    const std::vector<Button>& getButtons() const { return buttons; }
    ALLEGRO_FONT* getFont() const { return font; }

};


#endif