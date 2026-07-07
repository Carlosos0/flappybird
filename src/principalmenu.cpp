#include <allegro5/allegro_image.h>
#include <stdio.h> 
#include "graphloader.hpp" 
#include "principalmenu.hpp"

PrincipalMenu::PrincipalMenu(ALLEGRO_DISPLAY* display) {

    // Plano de fundo do menu
    backgroundX = 0; 
    background = graphloader::ScaleBitmap("./assets/fpbkg1.png", 800, 600, display); 
    fontMenu = al_load_font("./assets/PressStart2P-Regular.ttf", 20, 0);  
    fontTitle = al_load_font("./assets/PressStart2P-Regular.ttf", 52, 0); 
    
    if (!background) { printf("ERRO: Nao carregou o background do menu.\n"); }
    if (!fontMenu) { printf("ERRO: Nao carregou a fonte do menu.\n"); }
    if (!fontTitle) { printf("ERRO: Nao carregou a fonte do titulo.\n"); }

    // ENTRAR (LOGAR COM NOME DE USUARIO)
    buttons.push_back({250.0f, 200.0f, 300.0f, 50.0f, "ENTRAR", MenuState::Login});
    // CADASTRAR NOVO JOGADOR
    buttons.push_back({250.0f, 340.0f, 300.0f, 50.0f, "Cadastrar", MenuState::PlayerRegister});
    // SAIR DO JOGO
    buttons.push_back({250.0f, 410.0f, 300.0f, 50.0f, "SAIR", MenuState::Exit});
    // OPÇÕES
    buttons.push_back({250.0f, 250.0f, 300.0f, 50.0f, "OPÇÕES", MenuState::Options});
    // RANKING
    buttons.push_back({250.0f, 300.0f, 300.0f, 50.0f, "RANKING",  MenuState::Statistics});
    // buttons.push_back({250.0f, 410.0f, 300.0f, 50.0f, "Apagar Jogador", MenuState::DeletePlayer});
    Reset();
}

PrincipalMenu::~PrincipalMenu() {
    al_destroy_font(fontMenu);
    al_destroy_bitmap(background);
    al_destroy_font(fontTitle);
}

void PrincipalMenu::Draw() {
}

void PrincipalMenu::ProcessEvent(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        for (const auto& button : buttons) {
            if (CheckCollision(ev.mouse.x, ev.mouse.y, button)) {
                nextState = button.action;
                break; 
            }
        }
    }
}

MenuState PrincipalMenu::getNextState() {
    return nextState;
}

void PrincipalMenu::Reset() {
    nextState = MenuState::None;
}

bool PrincipalMenu::CheckCollision(float mouse_x, float mouse_y, const Button& button) {
    return (mouse_x >= button.x && mouse_x <= button.x + button.width &&
            mouse_y >= button.y && mouse_y <= button.y + button.height);
}

void PrincipalMenu::Update() {
    const float SCROLL_SPEED = 0.5f; 

    backgroundX -= SCROLL_SPEED;
    if (background) { 
        if (backgroundX <= -al_get_bitmap_width(background)) {
        
            backgroundX = 0;
        }
    }
}