#include "doublepipes.hpp"

vetor doublepipes::InvertPipePos(const Pipe& initPipe, float gap){
    vetor pipePos = initPipe.getPosition();
    float newY = pipePos.y - initPipe.getHeight() - gap;
    vetor invert = vetor(pipePos.x, newY);
    return invert;   
}

doublepipes::doublepipes(const Pipe& initPipe, float gap) : 
bottom(initPipe.getPosition(), 
        initPipe.getImage(), 
        initPipe.getWidth(), 
        initPipe.getHeight(),
        true), // é do tipo bottom
top(doublepipes::InvertPipePos(initPipe, gap), 
    initPipe.getImage(), 
    initPipe.getWidth(), 
    initPipe.getHeight(),
    false) // não é do tipo bottom
{
    this->gap = gap;
}

doublepipes::~doublepipes(){}

const Pipe& doublepipes::getTop() const {
    return top;
}

const Pipe& doublepipes::getBottom() const {
    return bottom;
}

float doublepipes::getGap() const {
    return gap;
}

void doublepipes::DoubleMovement(){
    bottom.Movement();
    top.Movement();
}

bool doublepipes::OffScreen(){
    vetor out = vetor(0, 0);
    if (bottom.getPosition().x + bottom.getWidth() <= out.x && top.getPosition().x + top.getWidth() <= out.x)
    {
        return true;
    }
    return false;
}