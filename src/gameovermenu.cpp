#include <stdio.h>
#include "gameovermenu.hpp"

GameOverMenu::GameOverMenu(){
    font = al_load_font("./assets/PressStart2P-Regular.ttf", 18, 0);
    if (!font) { printf("ERRO: Nao carregou a fonte do menu.\n"); }
    const float LARGURA_BOTAO = 250.0f;
    const float ALTURA_BOTAO = 50.0f;
    const float POSICAO_X = (800 / 2) - (LARGURA_BOTAO / 2);
    buttons.push_back({POSICAO_X, 380.0f, LARGURA_BOTAO, ALTURA_BOTAO, "Recomeçar", MenuState::RestartGame});
    buttons.push_back({POSICAO_X, 440.0f, LARGURA_BOTAO, ALTURA_BOTAO, "Menu", MenuState::GoToMainMenu});

    Reset();
}

GameOverMenu::~GameOverMenu() {
    al_destroy_font(font);
  
}

void GameOverMenu::ProcessEvent(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        for (const auto& button : buttons) {
            if (CheckCollision(ev.mouse.x, ev.mouse.y, button)) {
                nextState = button.action;
                break;
            }
        }
    }
}

void GameOverMenu::Draw() {}
MenuState GameOverMenu::getNextState() { return nextState; }
void GameOverMenu::Reset() { nextState = MenuState::None; }
bool GameOverMenu::CheckCollision(float mx, float my, const Button& btn) {
    return (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height);
}