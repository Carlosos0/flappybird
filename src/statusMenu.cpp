#include "statusMenu.hpp"

StatusMenu::StatusMenu(ALLEGRO_DISPLAY* display) : nextState(MenuState::None) {
    font = al_load_font("./assets/PressStart2P-Regular.ttf", 20, 0);
    if (!font) {
        printf("ERRO: Nao carregou a fonte do menu de status.\n");
    }

    btnVoltar = {250.0f, 500.0f, 300.0f, 50.0f, "VOLTAR", MenuState::GoToMainMenu};
}

void StatusMenu::ProcessEvent(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (CheckCollision(ev.mouse.x, ev.mouse.y, btnVoltar)) {
            nextState = btnVoltar.action;
        }
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        nextState = MenuState::GoToMainMenu;
    }
}

bool StatusMenu::CheckCollision(float mx, float my, const Button& btn) {
    return (mx >= btn.x && mx <= btn.x + btn.width &&
            my >= btn.y && my <= btn.y + btn.height);
}

MenuState StatusMenu::getNextState() {
    return nextState;
}

void StatusMenu::Reset() {
    nextState = MenuState::None;
}

void StatusMenu::Draw(){}

