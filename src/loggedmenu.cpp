#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "graphloader.hpp"
#include "loggedmenu.hpp"

LoggedMenu::LoggedMenu(ALLEGRO_DISPLAY* display) {

    // Plano de fundo do menu
    backgroundX = 0; 
    background = graphloader::ScaleBitmap("./assets/earth.png", 800, 600, display); 
    fontMenu = al_load_font("./assets/PressStart2P-Regular.ttf", 20, 0);  
    
    if (!background) { printf("ERRO: Nao carregou o background do menu.\n"); }
    if (!fontMenu) { printf("ERRO: Nao carregou a fonte do menu.\n"); }

    // JOGAR
    buttons.push_back({250.0f, 280.0f, 300.0f, 50.0f, "JOGAR", MenuState::PlayGame});
    // OPÇÕES
    buttons.push_back({720.0f, 20.0f, 60.0f, 60.0f, "O", MenuState::Options});
    // RANKING
    buttons.push_back({720.0f, 90.0f, 60.0f, 60.0f, "RNK",  MenuState::Statistics});
    // SAIR DO JOGO
    buttons.push_back({250.0f, 420.0f, 300.0f, 50.0f, "SAIR", MenuState::Exit});
    // DESLOGAR
    buttons.push_back({20.0f, 20.0f, 60.0f, 60.0f, "<-", MenuState::Logout});
    // STATUS DO JOGADOR
    buttons.push_back({250.0f, 80.0f, 300.0f, 100.0f, "STATUS", MenuState::Status});
    // MAPA
    buttons.push_back({250.0f, 350.0f, 300.0f, 50.0f, "MAPAS", MenuState::Map});


    
    Reset();
}

LoggedMenu::~LoggedMenu() {
    al_destroy_font(fontMenu);
    al_destroy_bitmap(background);
}

bool LoggedMenu::CheckCollision(float mouse_x, float mouse_y, const Button& button) {
    return (mouse_x >= button.x && mouse_x <= button.x + button.width &&
            mouse_y >= button.y && mouse_y <= button.y + button.height);
}

void LoggedMenu::Draw() {}

void LoggedMenu::ProcessEvent(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        for (const auto& button : buttons) {
            if (CheckCollision(ev.mouse.x, ev.mouse.y, button)) {
                nextState = button.action;
                break; 
            }
        }
    }
}

MenuState LoggedMenu::getNextState() {
    return nextState;
}

void LoggedMenu::Reset() {
    nextState = MenuState::None;
}


void LoggedMenu::Update() {
    const float SCROLL_SPEED = 0.5f;
    backgroundX -= SCROLL_SPEED;
    if (background) {
        if (backgroundX <= -al_get_bitmap_width(background)) {
            backgroundX = 0;
        }
    }
}


