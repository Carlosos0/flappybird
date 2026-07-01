#ifndef BIRD_H
#define BIRD_H

#include <memory>

#include "ambience.hpp"
#include "gameobject.hpp"


class bird : public gameobject {

private:

    bool alive;
    float rotation;
    vetor jump = vetor(0, -8.52f);

    std::shared_ptr<ambience> planet;

public:

    bird(const vetor& position, ALLEGRO_BITMAP* image, float width, float heigth, bool alive, float rotation);
    ~bird();

    bool getAlive() const;
    void setAlive(bool alive);

    float getRotation() const;
    void RotationRange();

    vetor getJump() const;
    // a ideia é que o pulo seja um atributo não-alteravel, por isso não terá set

    void setAmbience(std::shared_ptr<ambience> planet);
    // será usado pra definir qual o "planeta" que vai aplicar gravidade no passaro

    void Movement() override;
    void JumpAct();

    void LimitHeight();
};

#endif