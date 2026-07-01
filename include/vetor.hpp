#ifndef VETOR_H
#define VETOR_H

struct vetor {

    float x, y;

    vetor(float x, float y);
    vetor();

    vetor operator+ (const vetor& otherVector) const;
    vetor operator+ (float valor) const;
    bool operator== (const vetor& otherVector) const;
    
};

#endif