#include "doctest.h"
#include "nicknameinput.hpp"
#include "menu.hpp" 

// Cria um evento simulando uma tecla como ENTER, ESC ou BACKSPACE
ALLEGRO_EVENT auxNckKeyEvent(int keycode) {
    ALLEGRO_EVENT event;
    event.type = ALLEGRO_EVENT_KEY_DOWN;
    event.keyboard.keycode = keycode;
    return event;
}

// Cria um evento simulando a digitação de um caractere, como letras
ALLEGRO_EVENT auxNckCharEvent(char c) {
    ALLEGRO_EVENT event;
    event.type = ALLEGRO_EVENT_KEY_CHAR;
    event.keyboard.unichar = c;
    return event;
}

TEST_CASE("Testando a classe NicknameInput") {

    // Instancia o objeto responsável por receber o apelido digitado
    NicknameInput nickTester(nullptr);

    SUBCASE("Estado inicial e Reset") {
        // Verifica se o apelido começa vazio
        CHECK(nickTester.getNickname().empty() == true);

        // Verifica se não há mensagem de erro
        CHECK(nickTester.getErrorMessage().empty() == true);

        // Verifica se não há erro 
        CHECK(nickTester.hasError() == false);

        // Verifica se o estado inicial não manda pra outra tela
        CHECK(nickTester.getNextState() == MenuState::None);

        // Simula digitação de uma letra
        nickTester.ProcessEvent(auxNckCharEvent('A'));

        // Define uma mensagem de erro
        nickTester.setErrorMessage("Erro!");

        // Limpa todos os dados com o reset
        nickTester.Reset();

        // Verifica se tudo foi limpo corretamente
        CHECK(nickTester.getNickname().empty() == true);
        CHECK(nickTester.getErrorMessage().empty() == true);
        CHECK(nickTester.hasError() == false);
        CHECK(nickTester.getNextState() == MenuState::None);
    }

    SUBCASE("Digitação de caracteres e Backspace") {
        // Simula a digitação do apelido "Player"
        nickTester.ProcessEvent(auxNckCharEvent('P'));
        nickTester.ProcessEvent(auxNckCharEvent('l'));
        nickTester.ProcessEvent(auxNckCharEvent('a'));
        nickTester.ProcessEvent(auxNckCharEvent('y'));
        nickTester.ProcessEvent(auxNckCharEvent('e'));
        nickTester.ProcessEvent(auxNckCharEvent('r'));

        // Verifica se o apelido está correto
        CHECK(nickTester.getNickname() == "Player");

        // Simula dois backspaces, removendo 'r' e 'e'
        nickTester.ProcessEvent(auxNckKeyEvent(ALLEGRO_KEY_BACKSPACE));
        nickTester.ProcessEvent(auxNckKeyEvent(ALLEGRO_KEY_BACKSPACE));

        // Verifica se o apelido foi atualizado corretamente
        CHECK(nickTester.getNickname() == "Play");
    }

    SUBCASE("Limite de 20 caracteres") {
        // Tenta digitar 25 letras 'a', excedendo o limite
        for (int i = 0; i < 25; ++i) {
            nickTester.ProcessEvent(auxNckCharEvent('a'));
        }
        
        // Verifica se o limite de 20 foi respeitado
        CHECK(nickTester.getNickname().size() == 20);
        CHECK(nickTester.getNickname() == "aaaaaaaaaaaaaaaaaaaa");
    }

    SUBCASE("Navegação com ENTER e ESC") {
        // Simula ENTER para iniciar o jogo
        nickTester.ProcessEvent(auxNckKeyEvent(ALLEGRO_KEY_ENTER));
        CHECK(nickTester.getNextState() == MenuState::Game);

        // Reseta os dados
        nickTester.Reset();

        // Simula ESC para voltar ao menu principal
        nickTester.ProcessEvent(auxNckKeyEvent(ALLEGRO_KEY_ESCAPE));
        CHECK(nickTester.getNextState() == MenuState::GoToMainMenu);
    }

    SUBCASE("Configuração de mensagem de erro") {
        // Verifica que não há erro no início
        CHECK(nickTester.hasError() == false);

        // Define uma mensagem de erro
        nickTester.setErrorMessage("Apelido inválido");

        // Verifica se o erro foi ativado corretamente
        CHECK(nickTester.hasError() == true);
        CHECK(nickTester.getErrorMessage() == "Apelido inválido");
    }
}
