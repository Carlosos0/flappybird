#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <allegro5/allegro.h>

#include "vetor.hpp"

class gameobject {

protected:

    vetor position;
    ALLEGRO_BITMAP* image; 
    float width, height; 
    vetor move_speed;

public:

    gameobject();
    virtual ~gameobject();

    virtual void Movement() = 0; // totalmente abstrato

    ALLEGRO_BITMAP* getImage() const;
    void setImage(ALLEGRO_BITMAP* image);
    
    vetor getPosition() const;
    void setPosition(const vetor& position);

    float getWidth() const;
    void setWidth(float width);

    float getHeight() const;
    void setHeight(float height);

    vetor getMS() const;
    void setMS(const vetor& move_speed);

};

#endif