#ifndef LISTPLAYERS_HPP
#define LISTPLAYERS_HPP

#include <allegro5/allegro_font.h>
#include "menu.hpp"
#include "playermanager.hpp"

class ListPlayers : public Menu {
private:
    PlayerManager* playerManager;
    std::vector<Player> rankedPlayers;
    MenuState nextState;
    ALLEGRO_FONT* font;
    int scrollOffset;
    void refreshPlayerList();

public:
    ListPlayers(ALLEGRO_FONT* font, PlayerManager* manager);
    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    MenuState getNextState() override;
    void Reset() override;
    const std::vector<Player>& getPlayers() const { return rankedPlayers; }
    int getScrollOffset() const { return scrollOffset; }
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif