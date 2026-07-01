#include "exitConfirmMenu.hpp"
#include <allegro5/allegro_primitives.h>

ExitConfirmMenu::ExitConfirmMenu() {
    this->fontMenu = al_load_font("./assets/PressStart2P-Regular.ttf", 20, 0);
    if (!fontMenu) {
        printf("ERRO: Nao carregou a fonte do menu de confirmacao de saida.\n");
    }
}

ExitConfirmMenu::~ExitConfirmMenu() {
}

bool ExitConfirmMenu::CheckCollision(float mouse_x, float mouse_y, const Button& button) {
    return (mouse_x >= button.x && mouse_x <= button.x + button.width &&
            mouse_y >= button.y && mouse_y <= button.y + button.height);
}

void ExitConfirmMenu::Draw() {
    al_draw_filled_rectangle(0, 0, 800, 600, al_map_rgba(0, 0, 0, 150));
    al_draw_text(fontMenu, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Deseja sair do jogo?");
    al_draw_text(fontMenu, al_map_rgb(255, 255, 255), 400, 350, ALLEGRO_ALIGN_CENTER, "VOLTAR.");
    al_draw_text(fontMenu, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "SAIR.");
}

void ExitConfirmMenu::ProcessEvent(const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (CheckCollision(event.mouse.x, event.mouse.y, {300.0f, 300.0f, 200.0f, 50.0f, "SAIR", MenuState::Exit})) {
            nextState = MenuState::Exit;
        } else if (CheckCollision(event.mouse.x, event.mouse.y, {300.0f, 350.0f, 200.0f, 50.0f, "VOLTAR", MenuState::GoToMainMenu})) {
            nextState = MenuState::GoToMainMenu;
        }
    }
}

void ExitConfirmMenu::Reset() {
    nextState = MenuState::None;
}

MenuState ExitConfirmMenu::getNextState() {
    return nextState;
}
