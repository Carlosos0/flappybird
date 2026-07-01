#ifndef DOUBLEPIPES_H
#define DOUBLEPIPES_H

#include "pipe.hpp"

class doublepipes {

private:

    Pipe bottom;
    Pipe top;
    float gap;
    static vetor InvertPipePos(const Pipe& initPipe, float gap); // cria um cano baseado no outro

public:

    doublepipes(const Pipe& initPipe, float gap);
    ~doublepipes();

    const Pipe& getTop() const;
    const Pipe& getBottom() const;
    float getGap() const;
    
    void DoubleMovement();
    bool OffScreen();

};

#endif