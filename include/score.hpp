#ifndef SCORE_HPP
#define SCORE_HPP

#include "bird.hpp"
#include "doublepipes.hpp"
#include "pipeControl.hpp"

class score {
private:
    int currentScore;
    bool canScore; // quando ele ta passando por um cano, iria contar infinitas vezes na pontuação

public:
    score();
    ~score();
    
    int getCurrentScore() const;
    void setCurrentScore(int score);
    void resetScore();
    
    void updateScore(const bird& gameBird, const pipeControl& pipes);
};

#endif