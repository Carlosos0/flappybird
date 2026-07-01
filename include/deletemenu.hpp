#ifndef DELETE_MENU_HPP
#define DELETE_MENU_HPP

#include "menu.hpp"
#include "playermanager.hpp"
#include <allegro5/allegro_font.h>

class DeleteMenu : public Menu {
private:

    bool isConfirmingDelete = false;

    PlayerManager* playerManager;
    std::vector<Player> playerList;
    MenuState nextState;
    ALLEGRO_FONT* font;
    int highlightedIndex = -1;
    std::string nicknameToDelete;
    Button confirmButton;
    Button cancelButton;

    void refreshPlayerList();

public:
    DeleteMenu(ALLEGRO_FONT* font, PlayerManager* manager);
     ~DeleteMenu();
    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    void Reset() override;
    MenuState getNextState() override;
    bool isConfirming() const { return isConfirmingDelete; }
    
    const std::vector<Player>& getPlayers() const { return playerList; }
    int getHighlightedIndex() const { return highlightedIndex; }
    const Button& getConfirmButton() const { return confirmButton; }
    const Button& getCancelButton() const { return cancelButton; }
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif