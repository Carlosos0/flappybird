#include <iostream>
#include "deletemenu.hpp"

void DeleteMenu::refreshPlayerList() {
    if (playerManager) {
        playerList = playerManager->getRankedPlayers();
    }
}

DeleteMenu::DeleteMenu(ALLEGRO_FONT* a_font, PlayerManager* manager)
    : playerManager(manager), font(a_font), nextState(MenuState::None) {
    confirmButton = {275, 320, 100, 40, "Sim", MenuState::None};
    cancelButton = {425, 320, 100, 40, "Nao", MenuState::None};
    Reset();
}
DeleteMenu::~DeleteMenu() {
}
void DeleteMenu::Reset() {
    nextState = MenuState::None;
    isConfirmingDelete = false; 
    highlightedIndex = -1;
    nicknameToDelete = "";
    refreshPlayerList();
}

void DeleteMenu::ProcessEvent(const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        if (isConfirmingDelete) {
            isConfirmingDelete = false;
        } else {
            nextState = MenuState::GoToMainMenu;
        }
        return;
    }


    if (isConfirmingDelete) {

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
 
            if (event.mouse.x > confirmButton.x && event.mouse.x < confirmButton.x + confirmButton.width &&
                event.mouse.y > confirmButton.y && event.mouse.y < confirmButton.y + confirmButton.height) {
                playerManager->deletePlayer(nicknameToDelete);
                Reset();
            }
   
            else if (event.mouse.x > cancelButton.x && event.mouse.x < cancelButton.x + cancelButton.width &&
                     event.mouse.y > cancelButton.y && event.mouse.y < cancelButton.y + cancelButton.height) {
                isConfirmingDelete = false; 
        }
    } else {

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            highlightedIndex = -1;
            for (size_t i = 0; i < playerList.size(); ++i) {
                int offset = static_cast<int>(i) * 40;
                if (event.mouse.x > 600 && event.mouse.x < 700 &&
                    event.mouse.y > 150 + offset && event.mouse.y < 190 + offset) {
                    highlightedIndex = i;
                    break;
                }
            }
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && highlightedIndex != -1) {
            nicknameToDelete = playerList[highlightedIndex].nickname;
            isConfirmingDelete = true; 
        }
    }
}
}

MenuState DeleteMenu::getNextState() { return nextState; }
void DeleteMenu::Draw() {  }
