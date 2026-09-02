/**
 * @file graphloader.hpp
 * @brief Declaração da classe que renderiza e desenha os elementos gráficos.
 */

#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

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
#include "loggedmenu.hpp"
#include "mapMenu.hpp"
#include "nicknameinput.hpp"
#include "pipe.hpp"
#include "principalmenu.hpp"
#include "register.hpp"
#include "score.hpp"
#include "statusMenu.hpp"

/**
 * @class graphloader
 * @brief Renderiza os elementos gráficos: menus, objetos, botões, textos e imagens do jogo.
 */
class graphloader {
    
private:


    ALLEGRO_DISPLAY* display;       /// Ponteiro para a tela de exibição do jogo.

    /**
     * @brief Desenha um cano na tela.
     * @param obj Referência para o objeto Pipe a ser desenhado.
     */
    void DrawPipe(const Pipe& obj); 

public:

    /**
     * @brief Construtor padrão da classe graphloader.
     */
    graphloader();
    ~graphloader();

    /**
     * @brief Escala uma imagem para as dimensões especificadas.
     * @param filename Caminho do arquivo de imagem a ser escalada.
     * @param dw Largura desejada da imagem escalada.
     * @param dh Altura desejada da imagem escalada.
     * @param display Ponteiro para a tela de exibição do jogo.
     * @return Ponteiro para a imagem escalada.
     */
    static ALLEGRO_BITMAP* ScaleBitmap(const char* filename, float dw, float dh, ALLEGRO_DISPLAY* display);

    /**
     * @brief Inicializa a tela de exibição do jogo.
     * @param display Ponteiro para a tela de exibição do jogo.
     * @return true se a inicialização for bem-sucedida, false caso contrário.
     */
    bool InitDisplay(ALLEGRO_DISPLAY* display);

    /**
     * @brief Limpa a tela de exibição do jogo.
     */
    void Clear();

    /**
     * @brief Atualiza a tela de exibição do jogo.
     */
    void Update();

    /**
     * @brief Desenha o pássaro na tela.
     * @param obj Referência para o objeto Bird a ser desenhado.
     */
    void DrawBird(const bird& obj);

    /**
     * @brief Desenha o fundo do jogo.
     * @param background Ponteiro para a imagem de fundo do jogo.
     */
    void DrawBG(ALLEGRO_BITMAP* background);

    /**
     * @brief Desenha um par de canos na tela.
     * @param pipes Referência para o vetor de ponteiros únicos para os objetos DoublePipes a serem desenhados.
     */
    void DrawPipePair(const std::vector<std::unique_ptr<doublepipes>>& pipes);

    /**
     * @brief Desenha o chão na tela.
     * @param obj Referência para o objeto floor a ser desenhado.
     */
    void DrawFloor(const floor& obj);

    /**
     * @brief Desenha o menu na tela.
     * @param menu Referência para o objeto Menu a ser desenhado.
     */
    void DrawMenu(const PrincipalMenu& menu); 

    /**
     * @brief Desenha um botão na tela.
     * @param button Referência para o objeto Button a ser desenhado.
     * @param font Ponteiro para a fonte usada para desenhar o texto do botão.
     */
    void DrawButton(const Button& button, ALLEGRO_FONT* font);

    /**
     * @brief Desenha o menu de fim de jogo na tela.
     * @param menu Referência para o menu de game over a ser desenhado.
     * @param font Ponteiro para a fonte usada para desenhar o texto do menu.
     * @param currentScore Pontuação atual do jogador.
     * @param bestScore Melhor pontuação do jogador.
     * @param newRecord Indica se o jogador alcançou um novo recorde.
     */
    void DrawGameOverMenu(const GameOverMenu& menu, ALLEGRO_FONT* font, int currentScore, int bestScore, bool newRecord);

    /**
     * @brief Desenha o menu de registro na tela.
     * @param menu Referência para o menu de cadastro a ser desenhado.
     * @param font Ponteiro para a fonte usada para desenhar o texto do menu.
     */
    void DrawRegisterMenu(const Cadastro& menu, ALLEGRO_FONT* font);

    /**
     * @brief Desenha o menu de lista de jogadores na tela.
     * @param menu Referência para o menu de lista de jogadores a ser desenhado.
     */
    void DrawListPlayersMenu(const ListPlayers& menu);

    /**
     * @brief Desenha o menu de entrada de nickname na tela.
     * @param menu Referência para o menu de entrada de nickname a ser desenhado.
     * @param font Ponteiro para a fonte usada para desenhar o texto do menu.
     */
    void DrawNicknameInputMenu(const NicknameInput& menu, ALLEGRO_FONT* font);

    /**
     * @brief Desenha o menu de exclusão de jogador na tela.
     * @param menu Referência para o menu de exclusão de jogador a ser desenhado.
     */
    void DrawDeleteMenu(const DeleteMenu& menu);

    /**
     * @brief Desenha o menu de confirmação de saída.
     * @param menu Referência para o menu a ser desenhado.
     */
    void DrawExitConfirmMenu(const ExitConfirmMenu& menu);

    /**
     * @brief Desenha o menu de usuário loggado.
     * @param menu Referência para o menu a ser desenhado.
     * @param lgNickname Nickname do usuário loggado.
     * @param mapName Nome do mapa selecionado.
     */
    void DrawLoggedMenu(const LoggedMenu& menu, const std::string& lgNickname, const std::string& mapName);

    /**
     * @brief Desenha o menu de mapas.
     * @param menu Referência para o menu de mapas.
     * @param font Ponteiro para a fonte usada para desenhar o texto do menu.
     */
    void DrawMapMenu(const MapMenu& menu, ALLEGRO_FONT* font);

    /**
     * @brief Desenha o menu de status do jogador.
     * @param menu Referência para o menu de status.
     * @param player Referência para o jogador.
     */
    void DrawStatusMenu(const StatusMenu& menu, const Player& player);

    /**
     * @brief Desenha o menu de opções.
     * @param font Ponteiro para a fonte usada para desenhar o texto do menu.
     */
    void DrawOptionsMenu(ALLEGRO_FONT* font);

};

#endif