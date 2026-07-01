#include "doctest.h"
#include "crash.hpp"
#include "bird.hpp"
#include "pipeControl.hpp"
#include "floor.hpp"

TEST_CASE("Testando a classe Crash:") {

    Crash crashTester;

    SUBCASE("Verificando o estado inicial do detector de colisao:") {
        
        CHECK(crashTester.getFalling() == false); // estado inicial deve ser false
        CHECK(crashTester.getHitFloor() == false); // estado inicial deve ser false
        
    }

    SUBCASE("Verificando os setters e getters:") {
        
        crashTester.setFalling(true);
        CHECK(crashTester.getFalling() == true);
        
        crashTester.setHitFloor(true);
        CHECK(crashTester.getHitFloor() == true);
        
        crashTester.setFalling(false);
        CHECK(crashTester.getFalling() == false);
        
        crashTester.setHitFloor(false);
        CHECK(crashTester.getHitFloor() == false);
        
    }

    SUBCASE("Verificando detecao de intersecao de bounding box:") {
        
        // Teste básico de interseção
        CHECK(crashTester.intersectionBoundingBox(0, 0, 10, 10, 5, 5, 10, 10) == true);
        
        // Sem interseção - separados
        CHECK(crashTester.intersectionBoundingBox(0, 0, 10, 10, 15, 0, 10, 10) == false);
        CHECK(crashTester.intersectionBoundingBox(0, 0, 10, 10, 0, 15, 10, 10) == false);
        
        // Interseção apenas nas bordas (sem sobreposição)
        CHECK(crashTester.intersectionBoundingBox(0, 0, 10, 10, 10, 0, 10, 10) == false);
        CHECK(crashTester.intersectionBoundingBox(0, 0, 10, 10, 0, 10, 10, 10) == false);
        
    }

    SUBCASE("Verificando detecao de intersecao com floor:") {
        
        // Criar bird e floor para teste
        bird testBird(vetor(50, 90), nullptr, 10, 10, true, 0.0f);
        floor testFloor(vetor(0, 100), nullptr, 200, 20);
        
        // Configurar floor no detector
        crashTester.setFloor(std::make_shared<floor>(testFloor));
        
        // Bird acima do floor - sem colisão
        CHECK(crashTester.intersectionFloor(testBird) == false);
        
        // Mover bird para posição de colisão
        testBird.setPosition(vetor(50, 95));
        CHECK(crashTester.intersectionFloor(testBird) == true);
        
    }

}
