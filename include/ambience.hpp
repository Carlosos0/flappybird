#ifndef AMBIENCE_H
#define AMBIENCE_H

#include <allegro5/allegro.h>

#include "vetor.hpp"

class ambience {

private:

    vetor gravity;
    ALLEGRO_BITMAP* background;

public:

    ambience(vetor gravity, ALLEGRO_BITMAP* background);
    ~ambience();

    vetor getGravity() const;
    void setGravity(const vetor& gravity);

    ALLEGRO_BITMAP* getBackground() const;
    void setBackground(ALLEGRO_BITMAP* background);
};

#endif