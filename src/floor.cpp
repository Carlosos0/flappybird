#include "floor.hpp"

floor::floor(const vetor& position, ALLEGRO_BITMAP* image, float width, float height){
    setPosition(position);
    setImage(image);
    setWidth(width);
    setHeight(height);
    backgroundX = 0;
}

floor::~floor(){
}

void floor::Movement(){}
void floor::Update() {
    const float SCROLL_SPEED = 0.5f; 

    backgroundX -= SCROLL_SPEED;
    if (image) { 
        if (backgroundX <= -al_get_bitmap_width(image)) {
        
            backgroundX = 0;
        }
    }
}
