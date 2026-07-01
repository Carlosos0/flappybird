#include "ambience.hpp"

ambience::ambience(vetor gravity, ALLEGRO_BITMAP* background)
: gravity(gravity), background(background) {}

ambience::~ambience(){}

vetor ambience::getGravity() const {
    return gravity;
}

void ambience::setGravity(const vetor& gravity){
    this->gravity = gravity;
}

ALLEGRO_BITMAP* ambience::getBackground() const {
    return background;
}

void ambience::setBackground(ALLEGRO_BITMAP* background){
    this->background = background;
}