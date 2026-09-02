/**
 * @file gamecontroller.hpp
 * @brief Especifica a classe gamecontroller, que gerencia o fluxo do jogo.
 */
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

/**
 * @enum GameState
 * @brief Representa os diferentes estados do jogo.
 */
enum class GameState {
    mainmenu,               /// Estado do menu principal.
    NicknameInput,          /// Estado de entrada de nickname do jogador.
    PlayerRegister,         /// Estado de registro de jogador.
    Statistics,             /// Estado de exibição de estatísticas do jogador.
    DeletePlayer,           /// Estado de exclusão de jogador.
    Playing,                /// Estado de jogo em andamento.
    Paused,                 /// Estado de jogo pausado.
    GameOver,               /// Estado de fim de jogo.
    CountDown,              /// Estado de contagem regressiva antes do início do jogo.
    OptionsScreen,          /// Estado de tela de opções.
    LoggedMenu,             /// Estado de menu para jogador logado.
    StatusPlayer,           /// Estado de exibição de status do jogador.
    MapChooser,             /// Estado de escolha de mapa.
    ExitConfirm             /// Estado de confirmação de saída do jogo.
};

/**
 * @class gamecontroller
 * @brief Gerencia o fluxo do jogo, incluindo estados, eventos e lógica.
 */
class gamecontroller {

    private:

    static constexpr int SCREEN_W = 800;                /// Largura (width) da tela.
    static constexpr int SCREEN_H = 600;                /// Altura (height) da tela.
    static constexpr float gameBirdWidth = 51.0f;       /// Largura do pássaro.
    static constexpr float gameBirdHeight = 36.0f;      /// Altura do passáro.
    static constexpr float gamePipeWidth = 90.0f;       /// Largura do cano.
    static constexpr float gamePipeHeight = 400.0f;     /// Altura do cano.
    static constexpr float pipeGap = 150.0f;            /// Espaço entre os canos de um par.
    static constexpr float pipeDistance = 350.0f;       /// Distancia entre dois pares de canos.
    static constexpr float gameFloorHeight = 80.0f;     /// Altura do chão (bitmap do chão).

    const float FPS = 60.0;                             /// Taxa de quadros por segundo (frames per second) do jogo.
    bool playing = true;                                /// Indica se o jogo está em execução.
    bool redraw = true;                                 /// Indica se a tela precisa ser redesenhada.
    bool newRecord = false;                             /// Indica se o jogador obteve um novo recorde de pontuação.

    GameState currentState = GameState::mainmenu;       /// Estado atual do jogo.
    
    ALLEGRO_DISPLAY *display;                           /// Ponteiro para a tela do jogo.
    ALLEGRO_EVENT_QUEUE *queue;                         /// Ponteiro para a fila de eventos do jogo.
    ALLEGRO_TIMER *timer;                               /// Ponteiro para o timer, que controla a taxa de atualização do jogo.

    std::vector<ALLEGRO_BITMAP*> birdFrames;            /// Vetor de imagens que representam os quadros de animação do pássaro.
        
    ALLEGRO_BITMAP* pipeImg[3] = { nullptr, nullptr, nullptr };     /// Vetor de ponteiros para as imagens dos canos.
    ALLEGRO_BITMAP* bkgImg[3] = { nullptr, nullptr, nullptr };      /// Vetor de ponteiros para as imagens de fundo do jogo.
    ALLEGRO_BITMAP* floorImg[3] = { nullptr, nullptr, nullptr };    /// Vetor de ponteiros para as imagens do chão do jogo.
    ALLEGRO_BITMAP* menuPrincipalImg = nullptr;                     /// Ponteiro para a imagem de fundo do menu principal.
    ALLEGRO_FONT* loadingFont = nullptr;                            /// Ponteiro para a fonte utilizada na tela de carregamento.
    ALLEGRO_FONT* scoreFont = nullptr;                              /// Ponteiro para a fonte utilizada na exibição da pontuação do jogador.
    ALLEGRO_FONT* menuFont = nullptr;                               /// Ponteiro para a fonte utilizada nos botões do menu.
    ALLEGRO_FONT* smallFont = nullptr;                              /// Ponteiro para a fonte utilizada em textos menores.                      
    ALLEGRO_FONT* gameOverFont = nullptr;                           /// Ponteiro para a fonte utilizada na tela de fim de jogo.

    std::shared_ptr<ambience> gameAmbience = nullptr;               /// Ponteiro inteligente para ambience, que representa o cenário e gravidade do jogo.
    std::unique_ptr<bird> gameBird = nullptr;                       /// Ponteiro inteligente para bird, que representa o pássaro do jogo.
    std::unique_ptr<pipeControl> gamePControl = nullptr;            /// Ponteiro inteligente para pipeControl, que gerencia os pares de canos do jogo.
    std::shared_ptr<floor> gameFloor = nullptr;                     /// Ponteiro inteligente para floor, que representa o chão do jogo.
    std::unique_ptr<score> gameScore = nullptr;                     /// Ponteiro inteligente para score, que gerencia a pontuação do jogador.
    std::unique_ptr<Crash> gameCrash = nullptr;                     /// Ponteiro inteligente para Crash, que gerencia as colisões do pássaro com canos e chão.
    std::unique_ptr<PrincipalMenu> gameMenu = nullptr;              /// Ponteiro inteligente para PrincipalMenu, que representa o menu principal do jogo.
    std::unique_ptr<GameOverMenu> gameoverMenu = nullptr;           /// Ponteiro inteligente para GameOverMenu, que representa o menu de fim de jogo.
    std::unique_ptr<Cadastro> registerMenu = nullptr;               /// Ponteiro inteligente para Cadastro, que representa o menu de registro de jogador.
    std::unique_ptr<ListPlayers> listPlayersMenu = nullptr;         /// Ponteiro inteligente para ListPlayers, que representa o menu de lista de jogadores.
    std::unique_ptr<PlayerManager> playerManager;                   /// Ponteiro inteligente para PlayerManager, que gerencia os jogadores cadastrados e suas pontuações.
    std::string currentPlayerNickname;                              /// Nickname do jogador atualmente logado.
    std::unique_ptr<NicknameInput> nicknameInputMenu;               /// Ponteiro inteligente para NicknameInput, que representa o menu de entrada de nickname do jogador.
    std::unique_ptr<DeleteMenu> deleteMenu;                         /// Ponteiro inteligente para DeleteMenu, que representa o menu de exclusão de jogador.
    std::unique_ptr<ExitConfirmMenu> exitConfirmMenu;               /// Ponteiro inteligente para ExitConfirmMenu, que representa o menu de confirmação de saída do jogo.
    std::unique_ptr<StatusMenu> statusMenu;                         /// Ponteiro inteligente para StatusMenu, que representa o menu de status do jogador.
    std::unique_ptr<MapMenu> mapMenu;                               /// Ponteiro inteligente para MapMenu, que representa o menu de seleção de mapas.
    std::unique_ptr<LoggedMenu> loggedMenu;                         /// Ponteiro inteligente para LoggedMenu, que representa o menu do jogador logado.

    graphloader gameLoader;                                         /// Instância de graphloader, que é responsável por carregar e desenhar os elementos gráficos do jogo.
    input gameInput;                                                /// Instância de input, que é responsável por processar os eventos de entrada do jogador (teclado, mouse, etc.).
    
    int countdownValue = 0;                                         /// Valor atual da contagem regressiva antes do início do jogo.
    double countdownStartTime = 0.0;                                /// Instante que a contagem regressiva começou.
    float deathTime = 0.0;                                          /// Instante que o jogador morreu.

    /**
     * @brief Configura um novo jogo, inicializando os elementos necessários.
     * Define a posição inicial do pássaro, reinicia a pontuação, e prepara os canos para o início do jogo.
     */
    void SetupNewGame();

    /**
     * @brief Inicia a contagem regressiva antes do início do jogo.
     * Define o valor inicial da contagem regressiva e registra o instante de início.
     */
    void StartCountdown();

    /**
     * @brief Atualiza a contagem regressiva, verificando se o tempo decorrido desde o início da contagem atingiu 1 segundo.
     * Se sim, decrementa o valor da contagem regressiva e atualiza o instante de início. Se a contagem regressiva atingir zero,
     * muda o estado do jogo para "Playing".
     */
    void UpdateCountdown();

    public:
    
    /**
     * @brief Construtor da classe gamecontroller.
     * Inicializa os ponteiros para a tela, fila de eventos e timer do jogo.
     * Também inicializa os elementos gráficos e de entrada do jogo.
     */
    gamecontroller();
    ~gamecontroller();

    /**
     * @brief Inicializa as ferramentas e recursos necessários para o jogo.
     * @return true se a inicialização for bem-sucedida, false caso contrário.
     */
    bool InitTools();

    /**
     * @brief Processa os eventos do jogo, como entrada do jogador e eventos do timer.
     * @param event Referência para o evento a ser processado.
     */
    void EventsProcessor(const ALLEGRO_EVENT& event);

    /**
     * @brief Atualiza a lógica do jogo, incluindo o estado do pássaro, canos, pontuação e colisões.
     * Dependendo do estado atual do jogo, realiza diferentes ações, como iniciar a contagem regressiva, 
     * atualizar a pontuação, verificar colisões e gerenciar os menus do jogo. 
     */
    void Logic();

    /**
     * @brief Renderiza os elementos gráficos do jogo na tela.
     * Dependendo do estado atual do jogo, desenha diferentes elementos, como o fundo, pássaro, canos, chão, pontuação e menus.
     */
    void Render();

    /**
     * @brief Limpa a memória alocada para os elementos gráficos e recursos do jogo.
     * Libera a memória alocada para as imagens, fontes e outros recursos utilizados no
     * jogo, garantindo que não haja vazamentos de memória.
     */
    void MemoryClear();

    /**
     * @brief Executa o loop principal do jogo, processando eventos, atualizando a lógica e renderizando os elementos gráficos.
     * O loop continua enquanto a variável "playing" for verdadeira, permitindo que o jogo seja executado até que o jogador
     * decida sair ou o jogo seja encerrado.
     */
    void Run();

    /**
     * @return Ponteiro para a tela do jogo.
     */
    ALLEGRO_DISPLAY* getDisplay() const;

    /**
     * @return Ponteiro para a fila de eventos do jogo.
     */
    ALLEGRO_EVENT_QUEUE* getEventQueue() const;
    
};

#endif