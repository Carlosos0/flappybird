#ifndef PRINCIPALMENU_HPP
#define PRINCIPALMENU_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <vector>       
 
#include "menu.hpp"      

class PrincipalMenu : public Menu {
private:
    ALLEGRO_BITMAP* background;
    ALLEGRO_FONT* fontMenu;
    ALLEGRO_FONT* fontTitle;
    ALLEGRO_AUDIO_STREAM* musicMenu;
    
    std::vector<Button> buttons;
      float backgroundX;
    MenuState nextState; 
    bool CheckCollision(float mouse_x, float mouse_y, const Button& button); 

public:
    PrincipalMenu(ALLEGRO_DISPLAY* display);
    ~PrincipalMenu();

    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    ALLEGRO_BITMAP* getBackground() const { return background; }
    ALLEGRO_FONT* getFont() const { return fontMenu; }
    const std::vector<Button>& getButtons() const { return buttons; }
    float getBackgroundX() const { return backgroundX; }
    ALLEGRO_FONT* getFontTitle() const { return fontTitle; }
    MenuState getNextState() override; 
    void Reset() override;
    void Update();
};

#endif