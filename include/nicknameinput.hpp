#ifndef NICKNAMEINPUT_HPP
#define NICKNAMEINPUT_HPP

#include <allegro5/allegro_font.h>
#include "menu.hpp"

class NicknameInput : public Menu {
private:
    std::string currentNickname;
    std::string errorMessage;
    bool showError;
    MenuState nextState;
    ALLEGRO_FONT* font;

public:
    NicknameInput(ALLEGRO_FONT* font);
    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    MenuState getNextState() override;
    void Reset() override;
    void setErrorMessage(const std::string& message);
    std::string getNickname() const { return currentNickname; }
    std::string getErrorMessage() const { return errorMessage; }
    bool hasError() const { return showError; }
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif