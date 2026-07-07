#ifndef LOGGEDMENU_HPP
#define LOGGEDMENU_HPP

#include <allegro5/allegro_font.h>
#include <string>
#include <vector>

#include "menu.hpp"

class LoggedMenu : public Menu {

private:
    ALLEGRO_BITMAP* background;
    ALLEGRO_FONT* fontMenu;

    float backgroundX;
    std::vector<Button> buttons;
    MenuState nextState; 
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);

public:
    LoggedMenu(ALLEGRO_DISPLAY* display);
    ~LoggedMenu();

    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;

    ALLEGRO_BITMAP* getBackground() const { return background; }
    ALLEGRO_FONT* getFont() const { return fontMenu; }
    const std::vector<Button>& getButtons() const { return buttons; }
    float getBackgroundX() const { return backgroundX; }
    MenuState getNextState() override;
    void Reset() override;
    void Update();

};

#endif