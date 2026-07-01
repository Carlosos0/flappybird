#include "doctest.h"
#include "playermanager.hpp"
#include "menu.hpp"
#include "register.hpp"

#include <fstream>
#include <memory>

// Função auxiliar para criar eventos de pressionamento de tecla
ALLEGRO_EVENT auxKeyEvent(int keycode) {
    ALLEGRO_EVENT event;
    event.type = ALLEGRO_EVENT_KEY_DOWN;
    event.keyboard.keycode = keycode;
    return event;
}

// Função auxiliar para criar eventos de caracteres digitados
ALLEGRO_EVENT auxCharEvent(char c) {
    ALLEGRO_EVENT event;
    event.type = ALLEGRO_EVENT_KEY_CHAR;
    event.keyboard.unichar = c;
    return event;
}

TEST_CASE ("Testando a classe register:") {

    // Limpa o arquivo de jogadores antes de começar
    std::ofstream ofs("jogadores.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // Cria o objeto playerManager e o objeto de cadastro (regTester)
    auto playerManager = std::make_unique<PlayerManager>();
    Cadastro regTester(nullptr, nullptr, playerManager.get());

    SUBCASE ("Verificando cadastro bem sucedido:") {

        regTester.Reset(); // Reseta o estado do cadastro

        // Simula a digitação do nome "Hector"
        regTester.ProcessEvent(auxCharEvent('H'));
        regTester.ProcessEvent(auxCharEvent('e'));
        regTester.ProcessEvent(auxCharEvent('c'));
        regTester.ProcessEvent(auxCharEvent('t'));
        regTester.ProcessEvent(auxCharEvent('o'));
        regTester.ProcessEvent(auxCharEvent('r'));

        // Simula o pressionamento da tecla TAB para mudar de campo
        regTester.ProcessEvent(auxKeyEvent(ALLEGRO_KEY_TAB));

        // Simula a digitação do sobrenome "Hec"
        regTester.ProcessEvent(auxCharEvent('H'));
        regTester.ProcessEvent(auxCharEvent('e'));
        regTester.ProcessEvent(auxCharEvent('c'));

        // Simula o pressionamento da tecla ENTER para submeter o cadastro
        regTester.ProcessEvent(auxKeyEvent(ALLEGRO_KEY_ENTER));

        // Verifica se o próximo estado é o menu principal (cadastro bem-sucedido)
        CHECK(regTester.getNextState() == MenuState::GoToMainMenu);

        // Verifica se o jogador foi registrado corretamente
        CHECK(playerManager->nicknameExists("Hec") == true);
    }

    SUBCASE ("Verificando cadastro de usuário que já existe:") {
        regTester.Reset(); // Reseta o estado do cadastro

        // Adiciona um jogador fictício para garantir que o nome esteja ocupado
        playerManager->addNewPlayer("Outro Nome", "Test");

        // Tenta registrar um nome já existente
        regTester.ProcessEvent(auxCharEvent('N')); 
        regTester.ProcessEvent(auxKeyEvent(ALLEGRO_KEY_TAB));
        regTester.ProcessEvent(auxCharEvent('T')); 
        regTester.ProcessEvent(auxCharEvent('e'));
        regTester.ProcessEvent(auxCharEvent('s'));
        regTester.ProcessEvent(auxCharEvent('t'));
        regTester.ProcessEvent(auxKeyEvent(ALLEGRO_KEY_ENTER));

        // Verifica se o estado não mudou, pois o nome já existe
        CHECK(regTester.getNextState() == MenuState::None);
    }
}
