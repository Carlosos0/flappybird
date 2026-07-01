#include "ambience.hpp"
#include "doctest.h"
#include "vetor.hpp"

TEST_CASE ("Testando a classe Ambience:") {

    ambience ambTester(vetor(0.0f, 3.0f), nullptr);

    SUBCASE ("Verificando o estado inicial:") {
        // verifica se os dados foram inicializados como deveriam
        CHECK(ambTester.getGravity().x == 0.0f); 
        CHECK(ambTester.getGravity().y == 3.0f);
        CHECK(ambTester.getBackground() == nullptr);

    }

    SUBCASE ("Verificando a modificacao da gravidade (com setters):") {

        ambTester.setGravity(vetor(0.0f, 0.5f));

        CHECK(ambTester.getGravity().y == 0.5f); // verifica se houve alteração
        
        ambTester.setGravity(vetor(0.0f, -3.675f));

        CHECK(ambTester.getGravity().y == -3.675f); // verifica se houve alteração

    }
}