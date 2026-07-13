#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include "gamecontroller.hpp"

constexpr int gamecontroller::SCREEN_W;
constexpr int gamecontroller::SCREEN_H;
constexpr float gamecontroller::gameBirdWidth;
constexpr float gamecontroller::gameBirdHeight;
constexpr float gamecontroller::gamePipeWidth;
constexpr float gamecontroller::gamePipeHeight;
constexpr float gamecontroller::pipeGap;
constexpr float gamecontroller::pipeDistance;
constexpr float gamecontroller::gameFloorHeight;

gamecontroller::gamecontroller() {}

// --- DESTRUTOR ---
gamecontroller::~gamecontroller(){
    MemoryClear();
}

// --- GETTERS ---
ALLEGRO_DISPLAY* gamecontroller::getDisplay() const {
    return this->display;
}

ALLEGRO_EVENT_QUEUE* gamecontroller::getEventQueue() const {
    return this->queue;
}

void gamecontroller::SetupNewGame() {
    newRecord = false;

    int mapId = 0;
    if (mapMenu) {
        mapId = mapMenu->getSelectedMap();
    }

    gameAmbience->setBackground(bkgImg[mapId]);
    gameFloor->setImage(floorImg[mapId]);

    gameBird = std::make_unique<bird>(vetor(200, SCREEN_H / 2), birdImg, 
                gameBirdWidth, gameBirdHeight, true, 0.0f);
    gameBird->setAmbience(gameAmbience);

    gamePControl = std::make_unique<pipeControl>(pipeImg[mapId], 150, 350, 
                    gamePipeWidth, gamePipeHeight, SCREEN_W, SCREEN_H);
    
    gameCrash = std::make_unique<Crash>();
    gameCrash->setFloor(gameFloor);

    if (gameScore) {
        gameScore->resetScore();
    }
    
    if (!currentPlayerNickname.empty()) {
        playerManager->registerPlayer(currentPlayerNickname, mapId);
    }
    StartCountdown();
}

void gamecontroller::StartCountdown() {
    currentState = GameState::CountDown;
    countdownValue = 3; 
    countdownStartTime = al_get_time(); 
}

void gamecontroller::UpdateCountdown() {
    double currentTime = al_get_time();

    if (currentTime - countdownStartTime >= 1.0) {
        countdownValue--; 
        countdownStartTime = currentTime;

        if (countdownValue < 1) {
            currentState = GameState::Playing; 
        }
    }
}

// INICIALIZAÇÃO DAS FERRAMENTAS
bool gamecontroller::InitTools(){
    if (!al_init()) { return false; }
    
    srand(time(NULL)); 

    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    display = al_create_display(SCREEN_W, SCREEN_H);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    if (!display || !queue || !timer) { return false; }
    
    loadingFont = al_load_font("./assets/flapy.TTF", 30, 0);

    // TELA DE CARREGAMENTO
    if (loadingFont)    
    {
        gameLoader.Clear();
        al_draw_text(loadingFont, al_map_rgb(255, 0, 0), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Carregando..." );
        gameLoader.Update();
    }
    
    // Carregamento de assets

    // FONTES
    menuFont = al_load_font("./assets/flapy.TTF", 24, 0);
    smallFont = al_load_font("./assets/flapy.TTF", 18, 0);
    gameOverFont = al_load_font("./assets/flapy.TTF", 34, 0);
    scoreFont = al_load_font("./assets/DIMITRI_.TTF", 64, 0);

    // TERRA
    birdImg = graphloader::ScaleBitmap("./assets/bird.png", gameBirdWidth, gameBirdHeight, display);
    pipeImg[0] = graphloader::ScaleBitmap("./assets/earthpipe.png", gamePipeWidth, gamePipeHeight, display);
    bkgImg[0] = graphloader::ScaleBitmap("./assets/earth.png", SCREEN_W, SCREEN_H, display);
    floorImg[0] = graphloader::ScaleBitmap("./assets/earthfloor.png", SCREEN_W, gameFloorHeight, display);

    // LUA
    pipeImg[1] = graphloader::ScaleBitmap("./assets/moonpipe.png", gamePipeWidth, gamePipeHeight, display);
    bkgImg[1] = graphloader::ScaleBitmap("./assets/moon.png", SCREEN_W, SCREEN_H, display);
    floorImg[1] = graphloader::ScaleBitmap("./assets/moonfloor.png", SCREEN_W, gameFloorHeight, display);

    // MARTE
    pipeImg[2] = graphloader::ScaleBitmap("./assets/marspipe.png", gamePipeWidth, gamePipeHeight, display);
    bkgImg[2] = graphloader::ScaleBitmap("./assets/mars.png", SCREEN_W, SCREEN_H, display);
    floorImg[2] = graphloader::ScaleBitmap("./assets/marsfloor.png", SCREEN_W, gameFloorHeight, display);

    menuPrincipalImg = graphloader::ScaleBitmap("./assets/fpbkg1.png", SCREEN_W, SCREEN_H, display);
    
    if (!birdImg || !pipeImg[0] || !bkgImg[0] || !floorImg[0] || !pipeImg[1]|| !bkgImg[1] || !floorImg[1] || !pipeImg[2]|| !bkgImg[2] || !floorImg[2] || !loadingFont || !menuFont || !scoreFont || !smallFont) {
        std::cout << "FALHA NA INICIALIZACAO. VERIFICAR AS ASSETS CARREGADAS." << std::endl;
        MemoryClear();
        return false;
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    gameAmbience = std::make_shared<ambience>(vetor(0, 0.5f), bkgImg[0]);
    gameFloor = std::make_shared<floor>(vetor(0, SCREEN_H - gameFloorHeight), floorImg[0], SCREEN_W, gameFloorHeight);
    gameMenu = std::make_unique<PrincipalMenu>(display);
    gameoverMenu = std::make_unique<GameOverMenu>();
    gameScore = std::make_unique<score>();
    playerManager = std::make_unique<PlayerManager>();
    gameLoader.InitDisplay(display);
    nicknameInputMenu = std::make_unique<NicknameInput>(menuFont);
    registerMenu = std::make_unique<Cadastro>(display, menuFont, playerManager.get()); 
    listPlayersMenu = std::make_unique<ListPlayers>(menuFont, playerManager.get());
    deleteMenu = std::make_unique<DeleteMenu>(menuFont, playerManager.get());
    exitConfirmMenu = std::make_unique<ExitConfirmMenu>();
    loggedMenu = std::make_unique<LoggedMenu>(display);
    mapMenu = std::make_unique<MapMenu>(display);
    statusMenu = std::make_unique<StatusMenu>(display);
    return true;
}

// --- PROCESSADOR DE EVENTOS ---
void gamecontroller::EventsProcessor(const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        playing = false;
        return;
    }

    switch (currentState) {

        case GameState::mainmenu:

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                currentState = GameState::ExitConfirm;
                if (exitConfirmMenu)
                {
                    exitConfirmMenu->Reset();
                }
                gameMenu->Reset();
            }

            gameMenu->ProcessEvent(event);
            { 
                MenuState action = gameMenu->getNextState();
                
                // MENU PRINCIPAL DE LOGIN
                if (action == MenuState::Login) {
                    currentState = GameState::NicknameInput;
                    nicknameInputMenu->Reset();
                    gameMenu->Reset();
                }
                // CADASTRAR
                else if (action == MenuState::PlayerRegister) {
                    currentState = GameState::PlayerRegister;
                    registerMenu->Reset();
                    gameMenu->Reset();
                } 
                // SAIR DO JOGO        
                else if (action == MenuState::Exit) {
                    currentState = GameState::ExitConfirm;
                    if (exitConfirmMenu) {
                        exitConfirmMenu->Reset();
                    }
                    gameMenu->Reset();
                }
                // RANKING
                else if (action == MenuState::Statistics) {
                    currentState = GameState::Statistics;
                    listPlayersMenu->Reset();
                    gameMenu->Reset();
                }
                // OPÇÕES
                else if (action == MenuState::Options) {
                    currentState = GameState::OptionsScreen;
                    gameMenu->Reset();
                }
                break;
            }

        case GameState::NicknameInput:

            nicknameInputMenu->ProcessEvent(event);

            if (nicknameInputMenu->getNextState() == MenuState::GoToMainMenu) {
                currentState = GameState::mainmenu;
            } 
            else if (nicknameInputMenu->getNextState() == MenuState::Login) { 
                std::string nickname = nicknameInputMenu->getNickname();

                if (playerManager->nicknameExists(nickname)) {
                    currentPlayerNickname = nickname;
                    currentState = GameState::LoggedMenu;
                    loggedMenu->Reset();
                    mapMenu->mapReset();
                } else {
                    nicknameInputMenu->setErrorMessage("Apelido nao cadastrado!");
                }
            }
            break;

        case GameState::LoggedMenu:
            loggedMenu->ProcessEvent(event);
            {
                MenuState action = loggedMenu->getNextState();
                // JOGAR
                if (action == MenuState::PlayGame) {
                    SetupNewGame();
                    loggedMenu->Reset();
                }
                // OPCOES
                else if (action == MenuState::Options) {
                    currentState = GameState::OptionsScreen;
                    loggedMenu->Reset();
                }
                // RANKING
                else if (action == MenuState::Statistics) {
                    currentState = GameState::Statistics;
                    listPlayersMenu->Reset();
                }
                // STATUS
                else if (action == MenuState::Status) {
                    currentState = GameState::StatusPlayer;
                    // deleteMenu->Reset();
                }
                // LOGOUT
                else if (action == MenuState::Logout) {
                    currentPlayerNickname.clear();
                    currentState = GameState::mainmenu;
                    loggedMenu->Reset();
                    mapMenu->mapReset();
                    // ALTERAR: LOGOUT LEVA PRA UMA TELA (DESLOGAR OU DESLOGAR E SAIR)
                }
                // MAPA
                else if (action == MenuState::Map) {
                    currentState = GameState::MapChooser;
                    mapMenu->Reset();
                    loggedMenu->Reset();
                }
                // SAIR
                else if (action == MenuState::Exit) {
                    currentState = GameState::ExitConfirm;
                    if (exitConfirmMenu) {
                        exitConfirmMenu->Reset();
                    }
                    loggedMenu->Reset();
                }
            }
            break;

        case GameState::ExitConfirm:

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                if (currentPlayerNickname.empty()) {
                    currentState = GameState::mainmenu;
                }
                else {
                    currentState = GameState::LoggedMenu;
                }
                exitConfirmMenu->Reset();
            }
                
            exitConfirmMenu->ProcessEvent(event);
            {
                MenuState action = exitConfirmMenu->getNextState();
                if (action == MenuState::GoToMainMenu) {
                    if (currentPlayerNickname.empty()) {
                        currentState = GameState::mainmenu;
                    }
                    else {
                        currentState = GameState::LoggedMenu;
                    }
                    exitConfirmMenu->Reset();
                } 
                else if (action == MenuState::Exit) {
                    playing = false;
                }
                break;
            }

        case GameState::StatusPlayer:
            statusMenu->ProcessEvent(event);
            {
                if (statusMenu->getNextState() == MenuState::GoToMainMenu) {
                    currentState = GameState::LoggedMenu;
                    statusMenu->Reset();
                    loggedMenu->Reset();
                }
            }
            break;
            
        case GameState::MapChooser:
            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                currentState = GameState::LoggedMenu;
                mapMenu->Reset();
                loggedMenu->Reset();
                break;
            }

            mapMenu->ProcessEvent(event);
            {
                MenuState action = mapMenu->getNextState();

                if (action == MenuState::GoToMainMenu) {
                    currentState = GameState::LoggedMenu;
                    mapMenu->Reset();
                    loggedMenu->Reset();
                }
            }
            break;

        case GameState::DeletePlayer:
            deleteMenu->ProcessEvent(event);
            if (deleteMenu->getNextState() == MenuState::GoToMainMenu) {
                currentState = GameState::mainmenu;
            }
            break;

        case GameState::OptionsScreen:
            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                if (currentPlayerNickname.empty()) {
                    currentState = GameState::mainmenu;
                }
                else {
                    currentState = GameState::LoggedMenu;
                }
            }
            break;
            
        case GameState::PlayerRegister:
            registerMenu->ProcessEvent(event);
            {
                MenuState action = registerMenu->getNextState();
                if (action == MenuState::GoToMainMenu) {
                    currentState = GameState::mainmenu; 
                    registerMenu->Reset(); 
                } else if (action == MenuState::Exit) {
                    playing = false;
                }
            }
            break;
        
        case GameState::Statistics:

            listPlayersMenu->ProcessEvent(event);
            if (listPlayersMenu->getNextState() == MenuState::GoToMainMenu) {
                if(currentPlayerNickname.empty()) {
                    currentState = GameState::mainmenu;
                    loggedMenu->Reset();
                } 
                else {
                    currentState = GameState::LoggedMenu;
                    loggedMenu->Reset();
                }
                listPlayersMenu->Reset();
            }
            break;

        case GameState::Playing:

            gameInput.InputEvent(event);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                currentState = GameState::Paused;
            }
            break;

        case GameState::Paused:
            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                StartCountdown();
            }
            break;

        case GameState::GameOver:

            gameoverMenu->ProcessEvent(event);
            {
                MenuState action = gameoverMenu->getNextState();
                if (action == MenuState::RestartGame) {
                    SetupNewGame();
                    gameoverMenu->Reset();
                } else if (action == MenuState::GoToMainMenu) {
                    currentState = GameState::LoggedMenu;
                    gameoverMenu->Reset();
                }
            }
            break;

        case GameState::CountDown:
            break;
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
        ALLEGRO_EVENT nextEvent;
        while (al_peek_next_event(queue, &nextEvent)) {
            if (nextEvent.type == ALLEGRO_EVENT_TIMER) {
                al_drop_next_event(queue);
            } else {
                break;
            }
        }
        redraw = true;
        if (currentState == GameState::Playing) {
            Logic();
            gameFloor->Update();
        } else if (currentState == GameState::mainmenu) {
            gameMenu->Update(); 
        } else if (currentState == GameState::CountDown) {
            UpdateCountdown();
        } else if (currentState == GameState::LoggedMenu) {
            loggedMenu->Update();
        }
        else if (currentState == GameState::MapChooser) {
            mapMenu->Update();
        }
        
    }
}

// --- LÓGICA DO JOGO ---
void gamecontroller::Logic(){
    if (!gameBird) return;

    if (gameInput.getJumpInput() && gameBird->getAlive()) {
        gameBird->JumpAct();
    }
    gameInput.ResetJumpState();
    
    if (gameBird->getAlive()) {
        gameBird->Movement();
        gamePControl->PipeGenerator();
        gamePControl->UpdatePos();
        gamePControl->DeletePipes();
        gameCrash->checkCrash(*gameBird, *gamePControl);
        gameScore->updateScore(*gameBird, *gamePControl);
    } else {
        gameBird->Movement();
        gameCrash->checkCrash(*gameBird, *gamePControl);
        if (gameCrash->getHitFloor()) { 
            int finalScore = gameScore->getCurrentScore();
            if (!currentPlayerNickname.empty()) {
                int bestScore = playerManager->getHighScore(currentPlayerNickname);
                if (finalScore > bestScore) {
                    newRecord = true;
                }
                playerManager->updatePlayerScore(currentPlayerNickname, finalScore);
            }
            currentState = GameState::GameOver;
        }
    }
}

// --- RENDERIZAÇÃO ---
void gamecontroller::Render(){
    gameLoader.Clear();

    switch (currentState) {
        case GameState::mainmenu:
            gameLoader.DrawMenu(*gameMenu);
            break;
        case GameState::PlayerRegister:
            gameLoader.DrawRegisterMenu(*registerMenu, smallFont);
            break;
        case GameState::Statistics:
            gameLoader.DrawListPlayersMenu(*listPlayersMenu);
            break;
        case GameState::NicknameInput:
            gameLoader.DrawNicknameInputMenu(*nicknameInputMenu, smallFont);
            break;
        case GameState::DeletePlayer:
            gameLoader.DrawDeleteMenu(*deleteMenu);
            break;

        case GameState::LoggedMenu:
            gameLoader.DrawLoggedMenu(*loggedMenu, currentPlayerNickname, mapMenu->getSelectedMapName());
            break;
            
        case GameState::ExitConfirm:
            gameLoader.DrawExitConfirmMenu(*exitConfirmMenu);
            break;
        
        case GameState::MapChooser:
            gameLoader.DrawMapMenu(*mapMenu, menuFont);
            break;

        case GameState::StatusPlayer: 
        {
            Player p = playerManager->getPlayerInfo(currentPlayerNickname);
            gameLoader.DrawStatusMenu(*statusMenu, p);
            break;
        }
        
        case GameState::OptionsScreen:
            break;
        
        case GameState::Playing:
        case GameState::Paused:
        case GameState::CountDown:
        case GameState::GameOver:
            gameLoader.DrawBG(gameAmbience->getBackground());
            if (gamePControl) gameLoader.DrawPipePair(gamePControl->getPipeHouse());
            gameLoader.DrawFloor(*gameFloor);
            if (gameBird) gameLoader.DrawBird(*gameBird);
            
            if(gameScore) {
                std::string scoreText = "0" + std::to_string(gameScore->getCurrentScore());
                al_draw_text(scoreFont, al_map_rgb(255, 255, 255), 20, 20, ALLEGRO_ALIGN_LEFT, scoreText.c_str());
            }
            
            if (currentState == GameState::Paused) {
                al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgba(0, 0, 0, 150));
                al_draw_text(menuFont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 20, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");
            } else if (currentState == GameState::CountDown) {
                al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgba(0, 0, 0, 150));
                al_draw_textf(menuFont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "%d", countdownValue);
            } else if (currentState == GameState::GameOver) {
                if (gameoverMenu) {
                    int bestScore = playerManager->getHighScore(currentPlayerNickname);
                    gameLoader.DrawGameOverMenu(*gameoverMenu, gameOverFont, gameScore->getCurrentScore(), bestScore, newRecord);
                }
            }
            break;
    }   

    gameLoader.Update(); 
}

// --- LIMPEZA DE MEMÓRIA ---
void gamecontroller::MemoryClear(){
    
    for (int i = 0; i < 3; i++)
    {
        if (bkgImg[i]) al_destroy_bitmap(bkgImg[i]); bkgImg[i] = nullptr;
        if (pipeImg[i]) al_destroy_bitmap(pipeImg[i]); pipeImg[i] = nullptr;
        if (floorImg[i]) al_destroy_bitmap(floorImg[i]); floorImg[i] = nullptr;
    }
    
    al_destroy_bitmap(birdImg); birdImg = nullptr;
    al_destroy_bitmap(menuPrincipalImg); menuPrincipalImg = nullptr; 
    al_destroy_font(menuFont); menuFont = nullptr;
    al_destroy_font(loadingFont); loadingFont = nullptr;
    al_destroy_font(scoreFont); scoreFont = nullptr;
    al_destroy_font(gameOverFont); gameOverFont = nullptr;
    al_destroy_timer(timer); timer = nullptr;
    al_destroy_event_queue(queue); queue = nullptr;
    al_destroy_display(display); display = nullptr;
}

// --- LOOP PRINCIPAL ---
void gamecontroller::Run(){
    if(!InitTools()){
        std::cout << "FALHA NA INICIALIZACAO DE FERRAMENTAS." << std::endl;
        return;
    }
    
    al_start_timer(timer);
    
    while (playing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        EventsProcessor(event);

        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            Render();
        }
    }
}