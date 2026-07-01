#include "doctest.h"
#include "floor.hpp"
#include "vetor.hpp"

TEST_CASE ("Testando a classe floor:") {

    floor floorTester(vetor(0.0f, 520.0f), nullptr, 800.0f, 80.0f);

    SUBCASE ("Verificando o estado inicial do chao:") {

        CHECK(floorTester.getBackgroundX() == 0.0f); // a posição inicial do X deve ser 0

    }

    SUBCASE ("Verificando o movimento apos uma atualizacao:") {

        floorTester.Update();

        CHECK(floorTester.getBackgroundX() == doctest::Approx(-0.5f)); 

    }

    SUBCASE("Verificando o movimento apos atualizacoes multiplas:") {

        for (int i = 0; i < 7; i++) {
            floorTester.Update();
        }

        CHECK(floorTester.getBackgroundX() == doctest::Approx(-3.5f)); // verifica o movimento é 7 * variação de X
        
    }
}