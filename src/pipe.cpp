#include "pipe.hpp"

Pipe::Pipe(const vetor& position, ALLEGRO_BITMAP* image, float width, float height, bool bottomType)
: bottomType(bottomType)
{
    setPosition(position);
    setImage(image);
    setWidth(width);
    setHeight(height);
    setMS(vetor());
    
}

Pipe::~Pipe(){}

void Pipe::Movement(){
    vetor velocity = vetor(-5, 0);
    setMS(velocity);
    setPosition(getPosition() + getMS()); // mesma ideia do passaro, só que como nao recebe gravidade nem pulo é mais simples
}

bool Pipe::IsBottom() const{
    return this->bottomType;
}