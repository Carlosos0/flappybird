/**
 * @file listplayers.hpp
 * @brief Declaração da classe ListPlayers, menu de lista de jogadores.
 */
#ifndef LISTPLAYERS_HPP
#define LISTPLAYERS_HPP

#include <allegro5/allegro_font.h>
#include "menu.hpp"
#include "playermanager.hpp"

/** @class ListPlayers
 * @brief Menu de lista de jogadores.
 * Herda da classe Menu.
 */
class ListPlayers : public Menu {
private:
    PlayerManager* playerManager;       /// Ponteiro para o gerenciador de jogadores.
    std::vector<Player> rankedPlayers;  /// Vetor de jogadores classificados por pontuação.
    ALLEGRO_FONT* font;                 /// Ponteiro para a fonte utilizada no menu de lista de jogadores.                  
    MenuState nextState;                /// Estado do menu para o próximo estado após a interação do usuário.
    int scrollOffset;                   /// Deslocamento de rolagem (scroll do mouse) para a lista de jogadores.
    
    /** @brief Atualiza a lista de jogadores classificados.
     * Obtém a lista de jogadores do PlayerManager e atualiza o vetor rankedPlayers.
     */   
    void refreshPlayerList();           

public:

    /**
     * @brief Construtor da classe ListPlayers.
     * @param font Ponteiro para a fonte utilizada no menu de lista de jogadores.
     * @param manager Ponteiro para o gerenciador de jogadores.
     */
    ListPlayers(ALLEGRO_FONT* font, PlayerManager* manager);

    /** @brief Processador de eventos.
     * Aqui, os eventos processados são eventos de clique e rolagem do mouse.
     * @param event Evento do mouse.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /** @brief Desenha o menu de lista de jogadores.
     */
    void Draw() override;

    /**
     * @brief Obtém o próximo estado do menu.
     * @return O próximo estado do menu.
     */
    MenuState getNextState() override;

    /**
     * @brief Reseta o deslocamento de rolagem e atualiza a lista de jogadores
     * classificados.
     */
    void Reset() override;

    /**
     * @brief Obtém a lista de jogadores classificados.
     * @return Referência constante para o vetor de jogadores classificados,
     * ordenados por pontuação.
     */
    const std::vector<Player>& getPlayers() const { return rankedPlayers; }

    /**
     * @brief Obtém o deslocamento de rolagem atual.
     * @return O deslocamento do scroll.
     */
    int getScrollOffset() const { return scrollOffset; }

    /**
     * @brief Obtém a fonte utilizada no menu de lista de jogadores.
     * @return Ponteiro para a fonte.
     */
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif