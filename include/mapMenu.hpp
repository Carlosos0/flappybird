#ifndef MAPMENU_HPP
#define MAPMENU_HPP

#include <allegro5/allegro_font.h>
#include <string>
#include <vector>
#include "menu.hpp"

class MapMenu : public Menu {
private:

    ALLEGRO_BITMAP* background;
    ALLEGRO_FONT* fontMenu;
    std::vector<std::string> mapOptions;   
    int selectedMap;
    float backgroundX;
    MenuState nextState;

    bool CheckCollision(float mouse_x, float mouse_y, const Button& button);

    Button esqBtn;
    Button dirBtn;
    Button saveBtn;
    Button backBtn;
public:

    MapMenu(ALLEGRO_DISPLAY* display);
    ~MapMenu();

    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    void Reset() override;
    void Update();

    MenuState getNextState() override;

    int getSelectedMap() const { return selectedMap; }

    ALLEGRO_BITMAP* getBackground() const { return background; }
    float getBackgroundX() const { return backgroundX; }
    ALLEGRO_FONT* getFont() const { return fontMenu; }
    std::string getSelectedMapName() const { return mapOptions[selectedMap]; }
    void mapReset() { selectedMap = 0; }

    const Button& getLeftButton() const { return esqBtn; }
    const Button& getRightButton() const { return dirBtn; }
    const Button& getSaveButton() const { return saveBtn; }
    const Button& getBackButton() const { return backBtn; }

};
#endif