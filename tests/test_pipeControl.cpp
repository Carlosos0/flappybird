#include "doctest.h"
#include "pipeControl.hpp"
#include "vetor.hpp"

TEST_CASE ("Testando funções da classe pipeControl:") {

    float pipeGap = 130.0f;
    float pipeDistance = 300.0f;
    float pipeWidth = 90.0f;
    float pipeHeight = 400.0f;
    int SCREEN_W = 800.0f;
    int SCREEN_H = 600.0f;

    pipeControl pcTester(nullptr, pipeGap, pipeDistance, pipeWidth, pipeHeight, SCREEN_W, SCREEN_H);

    SUBCASE ("Verificando a logica de Spawn:") {

        CHECK(pcTester.getPipeHouse().empty() == true); // verifica se o vetor inicia vazio

        pcTester.PipeGenerator();
        CHECK(pcTester.getPipeHouse().size() == 1); // é possível gerar um cano, já que o vetor estava vazio

        pcTester.PipeGenerator();
        CHECK(pcTester.getPipeHouse().size() == 1); // só pode gerar outro cano se seguir a lógica do whenSpawn (vetor vazio ou posição = pipeDistance)

    }

    SUBCASE ("Verificando a logica de DeletePipes:") {

        pcTester.PipeGenerator();
        // SCREEN_w = 800, pipeWidth = 90. 
        // cada movimentação move em 5 pixeis o cano, 
        // logo, ele sai da tela após 890 / 5 = 178 atualizações
        for (int i = 0; i < 180.0f; i++) {
            pcTester.UpdatePos();
        }
        
        CHECK(pcTester.getPipeHouse().front()->OffScreen() == true); // o cano par de canos deve estar fora da tela

        pcTester.DeletePipes();

        CHECK(pcTester.getPipeHouse().empty() == true); // o cano fora da tela deve ser deletado, então o vetor deve estar vazio;
    
    }

}

TEST_CASE("Testando a geração de altura aleatória em pipeControl") {

    float pipeHeight = 400.0f;
    float SCREEN_H = 600.0f;

    pipeControl pcTester(nullptr, 150.0f, 350.0f, 90.0f, pipeHeight, 800.0f, SCREEN_H);
    
    // calcula as margens de geração de alturas para o cano bottom
    float minMargin = 135.0f;
    float maxY = SCREEN_H - minMargin; // Ex: 465
    float minY = SCREEN_H - pipeHeight;   // Ex: 200

    INFO("O valor de Y gerado deve estar entre " << minY << " e " << maxY);

    SUBCASE("RandHCalculator retorna valores dentro do intervalo esperado") {
        
        for (int i = 0; i < 1000; ++i) {
            int randY = pcTester.RandHCalculator();
            
            CHECK(randY >= minY); // randY nao pode ser menor que a altura minima
            CHECK(randY <= maxY); // randY nao pode ser maior que a altura maxima
        }
    }
}

