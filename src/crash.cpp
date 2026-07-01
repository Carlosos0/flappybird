#include "crash.hpp"

Crash::Crash() : falling(false), hitFloor(false), gameFloor(nullptr) {}

Crash::~Crash() {}

//verifica se há interseção entre duas bounding boxes 
bool Crash::intersectionBoundingBox(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) const {
    //      (x1 antes de w2)   (w1 depois de x2) (y1 acima de h2)  (h1 abaixo de y2)
    return ((x1 < x2 + w2) &&  (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2));
}

// função específica para colisão com o chão
bool Crash::intersectionFloor(const bird& personagem) const {
    if (!gameFloor) {
        return false; // Se não há floor definido, não há colisão
    }
    
    vetor birdPos = personagem.getPosition();
    vetor floorPos = gameFloor->getPosition();
    
    return intersectionBoundingBox(birdPos.x, birdPos.y, personagem.getWidth(), personagem.getHeight(),floorPos.x, floorPos.y, gameFloor->getWidth(), gameFloor->getHeight());
}

//verifica se o passaro colidiu com algum cano
bool Crash::intersectionPipe(const bird& personagem, const Pipe& pipe) const {
    vetor birdPos = personagem.getPosition();
    vetor pipePos = pipe.getPosition();
    
 
    
    // Dimensões da cabeça do cano 
    float headWidth = pipe.getWidth();
    float headHeight = pipe.getHeight() * 0.13f; 
    float headX = pipePos.x; 
    float headY = pipePos.y; 
    
    // Dimensões do corpo do cano
    float bodyWidth = pipe.getWidth() * 0.80f;
    float bodyHeight = pipe.getHeight() * 0.87f; 
    float bodyX = pipePos.x + 8;
    float bodyY = pipePos.y + headHeight; 
    
    // Verifica colisão com a cabeça do cano
    bool hitHead = intersectionBoundingBox(
        birdPos.x, birdPos.y, personagem.getWidth(), personagem.getHeight(),
        headX, headY, headWidth, headHeight
    );
    
    // Verifica colisão com o corpo do cano
    bool hitBody = intersectionBoundingBox(
        birdPos.x, birdPos.y, personagem.getWidth(), personagem.getHeight(),
        bodyX, bodyY, bodyWidth, bodyHeight
    );
    
    return hitHead || hitBody;
}

bool Crash::getFalling() const {
    return falling;
}

void Crash::setFalling(bool poscolisao) {
    falling = poscolisao;
}

bool Crash::getHitFloor() const {
    return hitFloor;
}

void Crash::setHitFloor(bool hit) {
    hitFloor = hit;
}

// Método para definir o objeto floor
void Crash::setFloor(std::shared_ptr<floor> gameFloor) {
    this->gameFloor = gameFloor;
}

//_____________________________________________________________________________________________
// FUNCAO PRINCIPAL DE CRASH
bool Crash::checkCrash(bird& personagem, const pipeControl& canos) {
    //verifica se ele ja esta caindo 
    if (!personagem.getAlive()) {
        // Se colidiu com o chão, para o pássaro
        if (intersectionFloor(personagem)) {
            if (!hitFloor) {
                setHitFloor(true);
                // Para o movimento e posiciona exatamente no topo do chão
                personagem.setMS(vetor(0, 0));
                if (gameFloor) {
                    vetor floorPos = gameFloor->getPosition();
                    personagem.setPosition(vetor(personagem.getPosition().x, floorPos.y - personagem.getHeight()));
                }
            }
        }
        return true;
    }
    
    //verifica colisão com o chão
    if (intersectionFloor(personagem)) {
        setFalling(true);
        personagem.setAlive(false);
        return true;
    }
    
    //verifica colisão com todos os pipes
    const auto& pipes = canos.getPipeHouse();
    for (const auto& pipePair : pipes) {
        //verifica se ha canos
        if (pipePair != nullptr) {
            //verifica colisão com o pipe de cima
            if (intersectionPipe(personagem, pipePair->getTop())) {
                setFalling(true);
                personagem.setAlive(false);
                return true;
            }
            
            //verifica colisão com o pipe de baixo
            if (intersectionPipe(personagem, pipePair->getBottom())) {
                setFalling(true);
                personagem.setAlive(false);
                return true;
            }
        }
    }
    
    return false;
}