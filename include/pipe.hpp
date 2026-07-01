#ifndef PIPE_H
#define PIPE_H

#include "gameobject.hpp"

class Pipe : public gameobject {

private:

    bool bottomType;

public:

    Pipe(const vetor& position, ALLEGRO_BITMAP* image, float width, float height, bool bottomType);
    ~Pipe();

    bool IsBottom() const;
    void Movement() override;
 
};

#endif