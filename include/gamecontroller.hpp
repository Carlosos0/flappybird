#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>   
#include <allegro5/allegro_ttf.h>  
#include <allegro5/allegro_primitives.h>

#include "ambience.hpp"
#include "bird.hpp"
#include "crash.hpp"
#include "deletemenu.hpp"
#include "exitConfirmMenu.hpp"
#include "floor.hpp"
#include "gameovermenu.hpp"
#include "graphloader.hpp"
#include "input.hpp"
#include "loggedmenu.hpp"
#include "nicknameinput.hpp"
#include "pipeControl.hpp"
#include "playermanager.hpp"
#include "principalmenu.hpp"
#include "register.hpp"
#include "score.hpp"
#include "statusMenu.hpp"


enum class GameState {
    mainmenu,
    NicknameInput,
    PlayerRegister,
    Statistics,
    DeletePlayer,
    Playing,
    Paused,
    GameOver,
    CountDown,
    OptionsScreen,
    LoggedMenu,
    StatusPlayer,
    MapChooser,
    ExitConfirm
};

class gamecontroller {

    private:

    static constexpr int SCREEN_W = 800;
    static constexpr int SCREEN_H = 600;
    static constexpr float gameBirdWidth = 51.0f;
    static constexpr float gameBirdHeight = 36.0f;
    static constexpr float gamePipeWidth = 90.0f;
    static constexpr float gamePipeHeight = 400.0f;
    static constexpr float pipeGap = 150.0f;
    static constexpr float pipeDistance = 350.0f;
    static constexpr float gameFloorHeight = 80.0f;

    const float FPS = 60.0;
    bool playing = true;
    bool redraw = true;
    bool newRecord = false;

    GameState currentState = GameState::mainmenu;
    
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;  
    
    ALLEGRO_BITMAP* birdImg = nullptr;
    ALLEGRO_BITMAP* pipeImg[3] = { nullptr, nullptr, nullptr };
    ALLEGRO_BITMAP* bkgImg[3] = { nullptr, nullptr, nullptr };
    ALLEGRO_BITMAP* floorImg[3] = { nullptr, nullptr, nullptr };
    ALLEGRO_BITMAP* menuPrincipalImg = nullptr;
    ALLEGRO_FONT* loadingFont = nullptr;
    ALLEGRO_FONT* scoreFont = nullptr;
    ALLEGRO_FONT* menuFont = nullptr;
    ALLEGRO_FONT* smallFont = nullptr;
    ALLEGRO_FONT* gameOverFont = nullptr;

    std::shared_ptr<ambience> gameAmbience = nullptr;
    std::unique_ptr<bird> gameBird = nullptr;
    std::unique_ptr<pipeControl> gamePControl = nullptr;
    std::shared_ptr<floor> gameFloor = nullptr;
    std::unique_ptr<score> gameScore = nullptr;
    std::unique_ptr<Crash> gameCrash = nullptr;
    std::unique_ptr<PrincipalMenu> gameMenu = nullptr;
    std::unique_ptr<GameOverMenu> gameoverMenu = nullptr;
    std::unique_ptr<Cadastro> registerMenu = nullptr;
    std::unique_ptr<ListPlayers> listPlayersMenu = nullptr;
    std::unique_ptr<PlayerManager> playerManager;
    std::string currentPlayerNickname;
    std::unique_ptr<NicknameInput> nicknameInputMenu;
    std::unique_ptr<DeleteMenu> deleteMenu;
    std::unique_ptr<ExitConfirmMenu> exitConfirmMenu;
    std::unique_ptr<LoggedMenu> loggedMenu;
    std::unique_ptr<MapMenu> mapMenu;
    std::unique_ptr<StatusMenu> statusMenu;

    graphloader gameLoader;
    input gameInput;
    
    int countdownValue = 0;
    double countdownStartTime = 0.0;

    void SetupNewGame();
    void StartCountdown();
    void UpdateCountdown();

    public:
  
    gamecontroller();
    ~gamecontroller();

    bool InitTools();
    void EventsProcessor(const ALLEGRO_EVENT& event);
    void Logic();
    void Render();
    void MemoryClear();
    void Run();

     // Getters públicos
    ALLEGRO_DISPLAY* getDisplay() const;
    ALLEGRO_EVENT_QUEUE* getEventQueue() const;
    
};

#endif