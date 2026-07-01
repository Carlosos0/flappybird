#include "score.hpp"

score::score() : currentScore(0), canScore(true) {}

score::~score() {}

int score::getCurrentScore() const {
    return currentScore;
}

void score::setCurrentScore(int score) {
    this->currentScore = score;
}

void score::resetScore() {
    currentScore = 0;
    canScore = true;
}

//----------------------------------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
void score::updateScore(const bird& gameBird, const pipeControl& pipes) {
    if (!gameBird.getAlive()) {
        return;
    }
    
    const auto& pipeHouse = pipes.getPipeHouse();
    vetor birdPos = gameBird.getPosition();
    
    bool birdIsPassingPipe = false;
    
    // Verifica se o pássaro está passando por algum cano
    for (const auto& pipePair : pipeHouse) {
        if (pipePair) {
            vetor pipePos = pipePair->getBottom().getPosition();
            float pipeWidth = pipePair->getBottom().getWidth();
            
            // birdIsPassingPip é true se ele ta passando pelo cano, isso impede ele de pontuar varias vezes
            if (birdPos.x >= pipePos.x && birdPos.x <= pipePos.x + pipeWidth) {
                birdIsPassingPipe = true;
                
                // Se pode pontuar e passou do meio do cano, incrementa a pontuação em 1
                if (canScore && birdPos.x > pipePos.x + pipeWidth/2) {
                    currentScore++;
                    canScore = false; // Impede de pontuar novamente até sair do meio do cano
                }
                break;
            }
        }
    }
    
    // Se não está passando por nenhum cano, pode pontuar novamente
    if (!birdIsPassingPipe) {
        canScore = true;
    }
}