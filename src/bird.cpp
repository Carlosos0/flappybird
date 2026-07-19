#include "ambience.hpp"
#include "bird.hpp"

bird::bird(const vetor& position, std::vector<ALLEGRO_BITMAP*> frames, float width, float height, bool alive, float rotation) 
: alive(alive), rotation(rotation), frames(frames), animationTimer(0), currentFrame(0) {
    setPosition(position);
    
    if (!frames.empty() && frames.size() == 4)
    {
        setImage(frames[0]); // asa começa pra cima
    }
    
    setWidth(width);
    setHeight(height);
    setMS(vetor()); 
}

bird::~bird() {}

bool bird::getAlive() const { // verificar se o bird está "vivo" no game ou nao
    return alive;
}

void bird::setAlive(bool alive) {
    this->alive = alive;
}

float bird::getRotation() const {
    return rotation;
}

void bird::RotationRange() {
    float aux = 0.1f;
    if (!alive) {
        rotation += 0.5f; 
        return;
    }
    if (getMS().y < 0)
    {
        rotation -= aux;
        if (rotation <= -0.4f) 
        {
            rotation = -0.4f;
        }
        
    }
    else if (getMS().y > 1.5)
    {
        rotation += aux;
        if (rotation >= 0.4f) {
            rotation = 0.4f;
        }
    }
}

vetor bird::getJump() const {
    return jump;
}

void bird::setAmbience(std::shared_ptr<ambience> planet){
    this->planet = planet;
}

void bird::Movement() {
    vetor newSpeed = getMS() + planet->getGravity();
    
    float maxSpeed = 10.0f;

    if (newSpeed.y > maxSpeed)
    {
        newSpeed.y = maxSpeed;
    }
    setMS(newSpeed);
    setPosition(getPosition() + getMS());
    LimitHeight();
    RotationRange();

    if (alive && frames.size() == 4) {
        animationTimer++;
    
        if (animationTimer > 3) {
        animationTimer = 0;
        currentFrame++;
        }
    
        if (currentFrame > 3) {
        currentFrame = 0;
        }
    
        if (currentFrame == 0) {
            setImage(frames[0]);
        } else if (currentFrame == 1 || currentFrame == 3) {
            setImage(frames[1]);
        } else if (currentFrame == 2) {
            setImage(frames[2]);
        } 
    } else if (!alive && frames.size() == 4) {
        setImage(frames[3]);
    }
    
    
}

void bird::JumpAct() {
    setMS(getJump());
}

void bird::LimitHeight() {
    vetor currentPos = getPosition();
    vetor currentSpeed = getMS();
    if (currentPos.y <= 0){
        setPosition(vetor(currentPos.x, 0));

        if (currentSpeed.y < 0) {
            setMS(vetor(currentSpeed.x, 0));
        }

}
}

