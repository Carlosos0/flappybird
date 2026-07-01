#include "doctest.h"
#include "vetor.hpp"

TEST_CASE ("Testando a classe vetor:") {

    SUBCASE ("Construtores:") {
        // testa o construtor padrão (sem argumentos)
        vetor vDefault;
        CHECK(vDefault.x == 0.0f);
        CHECK(vDefault.y == 0.0f);

        // testa o construtor com parâmetros
        vetor vParam(10.5f, -31354.0f);
        CHECK(vParam.x == 10.5f);
        CHECK(vParam.y == -31354.0f);
    }

    SUBCASE ("Operador de soma (+):") {

        vetor v1(5.0f, 10.0f);
        vetor v2(2.0f, -15.0f);
        
        // testa a soma de dois vetores
        vetor vSum = v1 + v2;
        CHECK(vSum.x == 7.0f);
        CHECK(vSum.y == -5.0f);
        
        // testa a soma de um vetor com um float
        vetor floatSum = v1 + 5.0f;
        CHECK(floatSum.x == 10.0f);
        CHECK(floatSum.y == 15.0f);

    }

    SUBCASE("Operador de igualdade (==)") {

        vetor v1(1.0f, 2.0f);
        vetor v2(1.0f, 2.0f);
        vetor v3(1.0f, 3.0f); // diferente em y
        vetor v4(3.0f, 2.0f); // diferente em x

        CHECK(v1 == v2); // deve ser verdadeiro
        CHECK_FALSE(v1 == v3); // deve ser falso
        CHECK_FALSE(v1 == v4); // deve ser falso
    }

}