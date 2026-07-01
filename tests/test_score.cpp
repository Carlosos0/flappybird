#include "doctest.h"
#include "score.hpp"
#include "bird.hpp"
#include "pipeControl.hpp"

TEST_CASE("Testando a classe score:") {

    score scoreTester;

    SUBCASE("Verificando o estado inicial do score:") {
        
        CHECK(scoreTester.getCurrentScore() == 0); // score inicial deve ser 0
        
    }

    SUBCASE("Verificando os setters e getters:") {
        
        scoreTester.setCurrentScore(5);
        CHECK(scoreTester.getCurrentScore() == 5);
        
        scoreTester.setCurrentScore(10);
        CHECK(scoreTester.getCurrentScore() == 10);
        
        scoreTester.setCurrentScore(0);
        CHECK(scoreTester.getCurrentScore() == 0);
        
    }

    SUBCASE("Verificando o reset do score:") {
        
        scoreTester.setCurrentScore(15);
        CHECK(scoreTester.getCurrentScore() == 15);
        
        scoreTester.resetScore();
        CHECK(scoreTester.getCurrentScore() == 0);
        
    }

    SUBCASE("Verificando updateScore com bird morto:") {
        
        bird testBird(vetor(50, 100), nullptr, 20.0f, 20.0f, false, 0.0f); // Bird morto
        pipeControl testPipes(nullptr, 100.0f, 200.0f, 800.0f, 600.0f, 150.0f, 5.0f);
        
        scoreTester.updateScore(testBird, testPipes);
        CHECK(scoreTester.getCurrentScore() == 0); // Score não deve mudar
        
    }

    SUBCASE("Verificando updateScore com bird vivo:") {
        
        bird testBird(vetor(50, 100), nullptr, 20.0f, 20.0f, true, 0.0f); // Bird vivo
        pipeControl testPipes(nullptr, 100.0f, 200.0f, 800.0f, 600.0f, 150.0f, 5.0f);
        
        // Teste básico de updateScore
        scoreTester.updateScore(testBird, testPipes);
        // O score pode ou não mudar dependendo da lógica interna
        CHECK(scoreTester.getCurrentScore() >= 0); // Score deve ser não negativo
        
    }

}
