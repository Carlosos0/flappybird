#ifndef GENERATION_H
#define GENERATION_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <vector>

#include "bird.hpp"
#include "deletemenu.hpp"
#include "doublepipes.hpp"
#include "exitConfirmMenu.hpp"
#include "floor.hpp"
#include "gameovermenu.hpp"
#include "listplayers.hpp"
#include "nicknameinput.hpp"
#include "pipe.hpp"
#include "principalmenu.hpp"
#include "register.hpp"
#include "score.hpp"

class graphloader {
    
private:

    ALLEGRO_DISPLAY* display;
    void DrawPipe(const Pipe& obj);

public:

    graphloader();
    ~graphloader();

    static ALLEGRO_BITMAP* ScaleBitmap(const char* filename, float dw, float dh, ALLEGRO_DISPLAY* display);
    bool InitDisplay(ALLEGRO_DISPLAY* display);
    void Clear();
    void Update();
    void DrawBird(const bird& obj);
    void DrawBG(ALLEGRO_BITMAP* background);
    void DrawPipePair(const std::vector<std::unique_ptr<doublepipes>>& pipes);
    void DrawFloor(const floor& obj);
    void DrawMenu(const PrincipalMenu& menu); 
    void DrawButton(const Button& button, ALLEGRO_FONT* font);
    void DrawGameOverMenu(const GameOverMenu& menu, ALLEGRO_FONT* font, int currentScore, int bestScore, bool newRecord);
    void DrawRegisterMenu(const Cadastro& menu, ALLEGRO_FONT* font);
    void DrawListPlayersMenu(const ListPlayers& menu);
    void DrawNicknameInputMenu(const NicknameInput& menu, ALLEGRO_FONT* font);
    void DrawDeleteMenu(const DeleteMenu& menu);
    void DrawExitConfirmMenu(const ExitConfirmMenu& menu);
};

#endif