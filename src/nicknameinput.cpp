#include "nicknameinput.hpp"

NicknameInput::NicknameInput(ALLEGRO_FONT* a_font) : font(a_font) { Reset(); }

void NicknameInput::Reset() {
    currentNickname.clear();
    errorMessage.clear();
    showError = false;
    nextState = MenuState::None;
}

void NicknameInput::setErrorMessage(const std::string& message) {
    errorMessage = message;
    showError = true;
    nextState = MenuState::None; 
}

void NicknameInput::ProcessEvent(const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode != ALLEGRO_KEY_ENTER) showError = false;
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE: nextState = MenuState::GoToMainMenu; break;
            case ALLEGRO_KEY_ENTER: case ALLEGRO_KEY_PAD_ENTER: nextState = MenuState::Game; break;
            case ALLEGRO_KEY_BACKSPACE: if (!currentNickname.empty()) currentNickname.pop_back(); break;
        }
    } else if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.unichar >= 32) {
        if (currentNickname.size() < 20) currentNickname += event.keyboard.unichar;
    }
}

MenuState NicknameInput::getNextState() { return nextState; }
void NicknameInput::Draw() {  }