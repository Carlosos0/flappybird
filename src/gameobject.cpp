#include "gameobject.hpp"

gameobject::gameobject(){}

gameobject::~gameobject(){}

ALLEGRO_BITMAP* gameobject::getImage() const {
    return image;
}

void gameobject::setImage(ALLEGRO_BITMAP* image){
    this->image = image;
}

vetor gameobject::getPosition() const {
    return position;
}

void gameobject::setPosition(const vetor& position){
    this->position = position;
}

float gameobject::getWidth() const {
    return width;
}

void gameobject::setWidth(float width) {
    this->width = width;
}

float gameobject::getHeight() const {
    return height;
}

void gameobject::setHeight(float height) {
    this->height = height;
}

vetor gameobject::getMS() const{
    return move_speed;
}

void gameobject::setMS(const vetor& move_speed){
    this->move_speed = move_speed;
}