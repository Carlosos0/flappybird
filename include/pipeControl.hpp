#ifndef PIPECONTROL_H
#define PIPECONTROL_H

#include <algorithm>
#include <memory>
#include <vector>

#include "doublepipes.hpp"

class pipeControl {

protected:

    std::vector<std::unique_ptr<doublepipes>> pipeHouse;
    ALLEGRO_BITMAP* pipeImg;

    float pipeGap;
    float pipeDistance;

    float pipeWidth;
    float pipeHeight;

    float SCREEN_W;
    float SCREEN_H;

public:

    pipeControl(ALLEGRO_BITMAP* pipeImg, float pipeGap, float pipeDistance, 
                float pipeWidht, float pipeHeight,        
                float SCREEN_W, float SCREEN_H);
        
    ~pipeControl();

    const std::vector<std::unique_ptr<doublepipes>>& getPipeHouse() const;

    int RandHCalculator();
    bool WhenSpawn();
    void PipeGenerator();
    void UpdatePos();
    void DeletePipes();
};

#endif