#include "vetor.hpp"

vetor::vetor(float x, float y) : x(x), y(y) {}
vetor::vetor(): x(0), y(0){}

vetor vetor::operator+(const vetor& other) const{
    return vetor(x + other.x, y + other.y);
}

vetor vetor::operator+(float value) const{
    return vetor(x + value, y + value);
}

bool vetor::operator==(const vetor& other) const {
    return x == other.x && y == other.y;
}


