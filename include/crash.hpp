#ifndef CRASH_H
#define CRASH_H

#include <memory>
#include <vector>

#include "bird.hpp"
#include "pipeControl.hpp"
#include "floor.hpp"

class Crash {

private:
    bool falling;
    bool hitFloor;
    std::shared_ptr<floor> gameFloor; 

public:
    Crash();
    ~Crash();

    bool intersectionBoundingBox(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) const;
    
    bool intersectionFloor(const bird& personagem) const; 
    
    bool intersectionPipe(const bird& personagem, const Pipe& pipe) const;

    bool getFalling() const;
    void setFalling(bool falling);
    
    bool getHitFloor() const;
    void setHitFloor(bool hit);

    void setFloor(std::shared_ptr<floor> gameFloor); 

    bool checkCrash(bird &personagem, const pipeControl &canos);
};

#endif