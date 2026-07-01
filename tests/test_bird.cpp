#include "ambience.hpp"
#include "bird.hpp"
#include "doctest.h"
#include "vetor.hpp"

TEST_CASE("Testando a classe bird:") {
    
    auto ambTester = std::make_shared<ambience>(vetor(0, 0.5f), nullptr);
    bird birdTester(vetor(100.0f, 300.0f), nullptr, 51.0f, 36.0f, true, 0.0f);
    birdTester.setAmbience(ambTester);

    SUBCASE("Teste de aplicacao de gravidade:") {

        CHECK(birdTester.getMS().y == 0.0f); // a velocidade inicial do pássaro deve ser 0

        birdTester.Movement();

        CHECK(birdTester.getMS().y == 0.5f); // a velocidade deve ser igual à gravidade
        CHECK(birdTester.getPosition().y == 300.5f); // a posição deve ser a inicial + velocidade

    }

    SUBCASE("JumpAct deve apenas alterar a velocidade, não a posição") {
       
        vetor posInicial = birdTester.getPosition();

        birdTester.JumpAct();   
        vetor jump = birdTester.getJump();

        // a velocidade vertical deve ser igual a do pulo.
        CHECK(birdTester.getMS().y == jump.y); 
        // a posição não deve mudar 
        CHECK(birdTester.getPosition().y == posInicial.y);
    }

    SUBCASE("Teste do ciclo completo: Pulo seguido de Movimento") {
        
        birdTester.JumpAct();
    
        birdTester.Movement();

        // nova velocidade = velocidade do pulo + a gravidade
        CHECK(birdTester.getMS().y == doctest::Approx(-8.52f + 0.5f)); // Aprox. -8.02f

        // nova posição = posição inicial (300) + nova velocidade (-8.02)
        CHECK(birdTester.getPosition().y == doctest::Approx(300.0f - 8.02f)); // Aprox. 291.98f
    }

    SUBCASE ("Testando o limite superior da tela:") {

        birdTester.setPosition(vetor(100.0f, 1.0f));
        birdTester.setMS(vetor(0.0f, -5.0f)); 
        birdTester.Movement();

        CHECK(birdTester.getPosition().y == 0.0f); // posição não pode passar de 0
        CHECK(birdTester.getMS().y >= 0.0f); // movespeed tem que ser zerada quando a posição y = 0

    }

    SUBCASE("Testando a rotacao para cima:") {

        birdTester.setMS(vetor(0.0f, -5.0f)); // teste com velocidade negativa (para cima)
        birdTester.RotationRange();

        CHECK(birdTester.getRotation() < 0.0f); // deve se inclinar para cima (rotação negativa)

    }

    SUBCASE ("Testando a rotacao para baixo:") {

        birdTester.setMS(vetor(0.0f, 2.0f)); // teste com velocidade positiva (para baixo)
        birdTester.RotationRange();

        CHECK(birdTester.getRotation() > 0.0f); // deve se inclinar para baixo (rotação positiva)
        
    }
}