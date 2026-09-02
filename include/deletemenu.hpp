/** 
 * @file deletemenu.hpp
 * @brief Declaração da classe DeleteMenu, que representa o menu de exclusão de jogadores.
*/

#ifndef DELETE_MENU_HPP
#define DELETE_MENU_HPP

#include "menu.hpp"
#include "playermanager.hpp"
#include <allegro5/allegro_font.h>

/**
 * @class DeleteMenu
 * @brief Representa o menu de exclusão de jogadores.
 * 
 * Permite ao usuário selecionar um jogador da lista e confirmar a exclusão.
 * Herda da classe Menu e implementa os métodos virtuais para processar eventos, desenhar o menu e gerenciar o estado do menu.
 */
class DeleteMenu : public Menu {
private:

    bool isConfirmingDelete = false;        /// Indica se o menu está aguardando confirmação de exclusão.
    PlayerManager* playerManager;           /// Ponteiro para o gerenciador de jogadores, usado para acessar e modificar a lista de jogadores.
    std::vector<Player> playerList;         /// Lista de jogadores carregada do PlayerManager.
    ALLEGRO_FONT* font;                     /// Ponteiro para a fonte usada para desenhar o texto no menu.
    MenuState nextState;                    /// Estado do menu para o próximo estado após a exclusão ou cancelamento.
    int highlightedIndex = -1;              /// Índice do jogador atualmente destacado na lista de jogadores.
    std::string nicknameToDelete;           /// Nickname do jogador selecionado para exclusão.
    Button confirmButton;                   /// Botão de confirmação de exclusão.
    Button cancelButton;                    /// Botão de cancelamento da exclusão.

    /**
     * @brief Atualiza a lista de jogadores carregando do PlayerManager.
     * 
     * Este método é chamado para garantir que a lista de jogadores exibida no menu esteja sempre atualizada.
     */
    void refreshPlayerList();

public:

    /**
     * @brief Construtor da classe DeleteMenu.
     * 
     * @param font Ponteiro para a fonte usada para desenhar o texto no menu.
     * @param manager Ponteiro para o gerenciador de jogadores.
     */
    DeleteMenu(ALLEGRO_FONT* font, PlayerManager* manager);
    ~DeleteMenu();

    /**
     * @brief Processa os eventos do menu, como cliques de mouse e teclas.
     * 
     * @param event Referência para o evento a ser processado.
     */
    void ProcessEvent(const ALLEGRO_EVENT& event) override;

    /**
     * @brief Desenha o menu na tela.
     * 
     * Responsável por renderizar a lista de jogadores, os botões de confirmação e cancelamento, e qualquer outro elemento visual do menu.
     */
    void Draw() override;

    /**
     * @brief Reseta o estado do menu para o estado inicial.
     * 
     * Este método é chamado quando o menu é reaberto, garantindo que nenhum estado anterior interfira na nova interação do usuário.
     */
    void Reset() override;

    /**
     * @brief Obtém o próximo estado do menu após a interação do usuário.
     */
    MenuState getNextState() override;

    /**
     * @brief Verifica se o menu está aguardando confirmação de exclusão.
     * @return true se o menu estiver aguardando confirmação, false caso contrário.
     */
    bool isConfirming() const { return isConfirmingDelete; }
    
    /**
     * @brief Obtém uma referência para a lista de jogadores carregada do PlayerManager.
     * @return Referência constante para o vetor de jogadores.
     */
    const std::vector<Player>& getPlayers() const { return playerList; }

    /**
     * @brief Obtém o índice do jogador destacado na lista.
     * @return Índice do jogador destacado.
     */
    int getHighlightedIndex() const { return highlightedIndex; }

    /**
     * @brief Obtém uma referência para o botão de confirmação.
     * @return Referência constante para o botão de confirmação.
     */
    const Button& getConfirmButton() const { return confirmButton; }

    /**
     * @brief Obtém uma referência para o botão de cancelamento.
     * @return Referência constante para o botão de cancelamento.
     */
    const Button& getCancelButton() const { return cancelButton; }

    /**
     * @brief Obtém uma referência para a fonte usada para desenhar o texto no menu.
     * @return Ponteiro para a fonte.
     */
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif