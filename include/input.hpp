#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>

class input {

private:

    bool jumpInput;
    bool quitInput;
    bool pauseInput;

public:

    input();
    ~input();

    bool getJumpInput() const;
    bool getQuitInput() const;
    bool getPauseInput() const;

    void ResetJumpState();
    void InputEvent(const ALLEGRO_EVENT &event);
   
};

#endif