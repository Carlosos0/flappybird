#ifndef FLOOR_H
#define FLOOR_H

#include "gameobject.hpp"
#include "vetor.hpp"

class floor: public gameobject {
    private:
    float backgroundX;

    public:

    floor(const vetor& position, ALLEGRO_BITMAP* image, float width, float height);
    ~floor();

    void Movement() override;
    void Update();
    float getBackgroundX() const { return backgroundX; }
};

#endif