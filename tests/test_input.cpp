#include "doctest.h"
#include "input.hpp"

TEST_CASE ("Testando a classe Input:") {
    
    input tester;

    SUBCASE ("Verificando o estado inicial das flags:") {
        // verifica se as flags iniciam com o estado false
        CHECK_FALSE(tester.getJumpInput());
        CHECK_FALSE(tester.getQuitInput());
        CHECK_FALSE(tester.getPauseInput());

    }

    SUBCASE ("Verificando o input de pulo (atualizacao das flags)") {
        
        ALLEGRO_EVENT jumpEvent;
        jumpEvent.type = ALLEGRO_EVENT_KEY_DOWN;
        jumpEvent.keyboard.keycode = ALLEGRO_KEY_SPACE;

        tester.InputEvent(jumpEvent);

        CHECK(tester.getJumpInput() == true); // verifica se o estado alterou 
        
        tester.ResetJumpState(); // flag de pulo deve ser resetada

        CHECK(tester.getJumpInput() == false); // verifica se após o input recebido, a flag vai ser resetada para false

    } 
    
    SUBCASE ("Verificando o input de pause:") {
    
        ALLEGRO_EVENT escEvent;
        escEvent.type = ALLEGRO_EVENT_KEY_DOWN;
        escEvent.keyboard.keycode = ALLEGRO_KEY_ESCAPE;

        tester.InputEvent(escEvent);

        CHECK(tester.getPauseInput() == true); // flag deve ser atualizada quando pressionado o esc

        tester.InputEvent(escEvent);

        CHECK(tester.getPauseInput() == false); // flag deve ser atualizada quando pressionado o esc

        tester.InputEvent(escEvent);

        CHECK(tester.getPauseInput() == true); // flag deve ser atualizada quando pressionado o esc
    
    }

    SUBCASE ("Verificando o input de quit") {
        
        ALLEGRO_EVENT quitEvent;
        quitEvent.type = ALLEGRO_EVENT_DISPLAY_CLOSE;

        tester.InputEvent(quitEvent);

        CHECK(tester.getQuitInput() == true); // flag de quit deve ser true quando o "close" for pressionado
    
    }
}