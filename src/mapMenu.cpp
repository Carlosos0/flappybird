#include "mapMenu.hpp"
#include "graphloader.hpp"

MapMenu::MapMenu(ALLEGRO_DISPLAY* display) : selectedMap(0), nextState(MenuState::None) {
    backgroundX = 0; 
    background = graphloader::ScaleBitmap("./assets/earth.png", 800, 600, display); 
    fontMenu = al_load_font("./assets/PressStart2P-Regular.ttf", 20, 0);  
    
    if (!background) { printf("ERRO: Nao carregou o background do menu.\n"); }
    if (!fontMenu) { printf("ERRO: Nao carregou a fonte do menu.\n"); }

    mapOptions = {"TERRA", "LUA", "MARTE"};

    esqBtn = {50.0f, 250.0f, 100.0f, 50.0f, "<", MenuState::None};
    dirBtn = {650.0f, 250.0f, 100.0f, 50.0f, ">", MenuState::None};
    saveBtn = {250.0f, 400.0f, 300.0f, 50.0f, "SALVAR", MenuState::GoToMainMenu};
    backBtn = {250.0f, 500.0f, 300.0f, 50.0f, "VOLTAR", MenuState::GoToMainMenu};

    Reset();
}

MapMenu::~MapMenu() {
    al_destroy_font(fontMenu);
    al_destroy_bitmap(background);
}

void MapMenu::ProcessEvent(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        float mx = ev.mouse.x;
        float my = ev.mouse.y;
        
        if (CheckCollision(mx, my, esqBtn)) {
            selectedMap--;
            if (selectedMap < 0) {
                selectedMap = mapOptions.size() - 1;
            }
        }
        else if (CheckCollision(mx, my, dirBtn)) {
            selectedMap++;
            if (selectedMap >= (int)mapOptions.size()) {
                selectedMap = 0;
            }
        }
        else if (CheckCollision(mx, my, saveBtn)) {
            nextState = saveBtn.action;
        }
        else if (CheckCollision(mx, my, backBtn)) {
            nextState = backBtn.action;
        }
    }
    
}

void MapMenu::Draw(){}

void MapMenu::Reset() {
    nextState = MenuState::None;
}

void MapMenu::Update() {
    const float SCROLL_SPEED = 0.5f;
    backgroundX -= SCROLL_SPEED;
    if (background) {
        if (backgroundX <= -al_get_bitmap_width(background)) {
            backgroundX = 0;
        }
    }
}

MenuState MapMenu::getNextState() {
    return nextState;
}

bool MapMenu::CheckCollision(float mouse_x, float mouse_y, const Button& button) {
    return (mouse_x >= button.x && mouse_x <= button.x + button.width &&
            mouse_y >= button.y && mouse_y <= button.y + button.height);
}