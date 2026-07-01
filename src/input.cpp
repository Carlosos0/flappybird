#include "input.hpp"

input::input() : jumpInput(false), quitInput(false), pauseInput(false) {}

input::~input(){}


bool input::getJumpInput() const {
    return this->jumpInput;
}

bool input::getQuitInput() const {
    return this->quitInput;
}

bool input::getPauseInput() const {
    return this->pauseInput;
}

void input::InputEvent(const ALLEGRO_EVENT &event){

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        quitInput = true;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode)
        {
        case ALLEGRO_KEY_SPACE:
            jumpInput = true;
        break;

        case ALLEGRO_KEY_ESCAPE:
            pauseInput = !pauseInput;
        }
    }
}

void input::ResetJumpState(){
    jumpInput = false;
}