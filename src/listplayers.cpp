#include "listplayers.hpp"

ListPlayers::ListPlayers(ALLEGRO_FONT* a_font, PlayerManager* manager) 
    : playerManager(manager), font(a_font), nextState(MenuState::None), scrollOffset(0) {
    Reset();
}

void ListPlayers::Reset() {
    nextState = MenuState::None;
    scrollOffset = 0;
    refreshPlayerList();
}

void ListPlayers::refreshPlayerList() {
    if (playerManager) {
        rankedPlayers = playerManager->getRankedPlayers();
    }
}

void ListPlayers::ProcessEvent(const ALLEGRO_EVENT& event) {
    if (event.type != ALLEGRO_EVENT_KEY_DOWN) return;
    switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE: nextState = MenuState::GoToMainMenu; break;
        case ALLEGRO_KEY_UP: if (scrollOffset > 0) scrollOffset--; break;
        case ALLEGRO_KEY_DOWN:
            if (!rankedPlayers.empty() && scrollOffset < static_cast<int>(rankedPlayers.size()) - 1) {
                scrollOffset++;
            }
            break;
    }
}

MenuState ListPlayers::getNextState() { return nextState; }
void ListPlayers::Draw() {  }