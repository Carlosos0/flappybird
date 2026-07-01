#include "doctest.h"
#include "doublepipes.hpp"
#include "pipe.hpp"
#include "vetor.hpp"

TEST_CASE ("Testando a classe doublepipes:") {

    float pipeHeight = 400.0f;
    Pipe btModel(vetor(300.0f, 480.0f), nullptr, 90.0f, pipeHeight, true);

    SUBCASE ("Verificando a posicao do cano de cima(top):") {

        float gap = 135.0f;
        doublepipes pairTester(btModel, gap);

        // verifica se a posição do cano de baixo está correta
        CHECK(pairTester.getBottom().getPosition().y == 480.0f); 
        CHECK(pairTester.getBottom().getPosition().x == 300.0f); 

        CHECK(pairTester.getTop().getPosition().y == doctest::Approx(-55.0f)); // verifica se a altura do cano de cima foi gerada corretamente

    }

    SUBCASE ("Verificando a condicao de OffScreen:") {

        Pipe OffsModel(vetor(-221.0f, 394.0f), nullptr, 90.0f, pipeHeight, true);
        doublepipes OffsPair(OffsModel, 134.04f);

        CHECK(OffsPair.OffScreen() == true); // verifica se o par está fora da tela

        Pipe InModel(vetor(136.0f, 400.0f), nullptr, 90.0f, pipeHeight, true);
        doublepipes InPair(InModel, 150.0f);

        CHECK(InPair.OffScreen() == false); // verifica se o par está dentro da tela

    }
}