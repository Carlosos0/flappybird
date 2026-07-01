#include <algorithm>
#include "pipeControl.hpp"

pipeControl::pipeControl(ALLEGRO_BITMAP* pipeImg, float pipeGap, float pipeDistance, 
                    float pipeWidth, float pipeHeight, float SCREEN_W, float SCREEN_H) :
                    pipeImg(pipeImg), pipeGap(pipeGap), pipeDistance(pipeDistance), 
                    pipeWidth(pipeWidth), pipeHeight(pipeHeight),
                    SCREEN_W(SCREEN_W), SCREEN_H(SCREEN_H) {}

pipeControl::~pipeControl(){}

const std::vector<std::unique_ptr<doublepipes>>& pipeControl::getPipeHouse() const {
    return pipeHouse;
}

int pipeControl::RandHCalculator(){
    int minH = 135;
    int min = SCREEN_H - minH;
    int max = SCREEN_H - this->pipeHeight;
    return min - rand() % (min - max);
}

bool pipeControl::WhenSpawn(){
    if (pipeHouse.empty())
    {
        return true;
    }
    else
    {
        const auto& lastPair = pipeHouse.back();
        if (lastPair->getBottom().getPosition().x < SCREEN_W - pipeDistance) // se a posição do par for menor que ex: 450, spawn = true
        {
            return true;
        }
        return false;
    }
}

void pipeControl::PipeGenerator(){
    if (WhenSpawn())
    {
        int randomY = RandHCalculator();
        vetor initPos = vetor(SCREEN_W, randomY);
        
        Pipe bottomModel(initPos, pipeImg, this->pipeWidth, this->pipeHeight, true);
       
        pipeHouse.push_back(std::make_unique<doublepipes>(bottomModel, pipeGap));
    }
}  

void pipeControl::UpdatePos(){
    for (const auto& pipePair : this->pipeHouse) {
        pipePair->DoubleMovement();
    }
}

void pipeControl::DeletePipes(){
    auto aux = remove_if(
        this->pipeHouse.begin(),
        this->pipeHouse.end(),
        []
        (const std::unique_ptr<doublepipes>& pipePair){
            return pipePair->OffScreen();
        }
    );
    this->pipeHouse.erase(aux, this->pipeHouse.end());
}
