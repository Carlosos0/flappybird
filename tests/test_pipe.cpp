#include "doctest.h"
#include "pipe.hpp"
#include "vetor.hpp"

TEST_CASE("Testando a Classe Pipe:") {

    Pipe testing(vetor(400.0f, 200.0f), nullptr, 50.0f, 300.0f, true);

    CHECK(testing.getPosition().x == 400.0f); // a posição do construtor deve ser passada ao objeto
    CHECK(testing.IsBottom() == true); // o objeto tem que ser do tipo bottom
    CHECK(testing.getHeight() == 300.0f); // a altura deve ser a mesma passada no construtor

    testing.Movement();

    CHECK(testing.getPosition().x == 395); // a posição tem que ser igual POSIÇAO_X + MOVESPEED_X (que no projeto é negativa)
    CHECK(testing.getPosition().y == 200.0f); // a posição no eixo Y não deve mudar

    for (int i = 0; i < 5; i++) {
        testing.Movement();
    }
    
    CHECK(testing.getPosition().x == 370.0f); // a posição deve ser igual a POSIÇÃO_X - (5 * MOVESPEED_X)
    CHECK(testing.getPosition().y == 200.0f); // a posição no eixo Y deve se manter a mesma

}