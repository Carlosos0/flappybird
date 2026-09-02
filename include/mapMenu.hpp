/**
 * @file mapMenu.hpp
 * @brief Declaração da classe MapMenu, utilizada para criar o menu de 
 * seleção de mapas.
 */
#ifndef MAPMENU_HPP
#define MAPMENU_HPP

#include <allegro5/allegro_font.h>
#include <string>
#include <vector>
#include "menu.hpp"

/**
 * @class MapMenu
 * @brief Menu de seleção de mapas.
 * Herda da classe Menu.
 */
class MapMenu : public Menu {
private:

    ALLEGRO_BITMAP* background;         /// Ponteiro para a imagem de fundo do menu de seleção de mapas.
    ALLEGRO_DISPLAY* display;           /// Ponteiro para a tela de exibição do jogo.
    ALLEGRO_FONT* font;                 /// Ponteiro para a fonte utilizada no menu de seleção de mapas.
    ALLEGRO_FONT* fontNickname;         /// Ponteiro para a fonte utilizada para exibir o nickname do usuário loggado.
    ALLEGRO_FONT* fontMap;              /// Ponteiro para a fonte utilizada para exibir o nome do mapa selecionado.
    ALLEGRO_FONT* fontMenu;             /// Ponteiro para a fonte utilizada para exibir o menu de seleção de mapas.
    std::vector<std::string> mapOptions; /// Vetor contendo os nomes dos mapas disponíveis para seleção.
    int selectedMap;                    /// Índice do mapa atualmente selecionado.
    float backgroundX;                  /// Posição x da imagem de fundo do menu de seleção de mapas.
    MenuState nextState;                /// Estado do menu para o próximo estado após a interação do usuário.

    bool CheckCollision(float mouse_x, float mouse_y, const Button& button); /// Verifica se o mouse está colidindo com um botão.

    Button esqBtn;          /// Botão para selecionar o mapa anterior. <-
    Button dirBtn;          /// Botão para selecionar o próximo mapa. ->
    Button saveBtn;         /// Botão para salvar a seleção do mapa atual.
    Button backBtn;         /// Botão para voltar ao menu anterior.

public:

    /**
     * @brief Construtor da classe MapMenu.
     * @param display Ponteiro para a tela de exibição do jogo.
     */
    MapMenu(ALLEGRO_DISPLAY* display);
    ~MapMenu();

    void ProcessEvent(const ALLEGRO_EVENT& event) override; /// Processador de eventos de entrada no menu.
    void Draw() override;                                   /// Desenha o menu de seleção de mapas na tela.
    void Reset() override;                                  /// Reseta o menu de seleção de mapas para o estado inicial.
    void Update();                                          /// Atualiza o estado após o mapa ser selecionado.

    MenuState getNextState() override;          /// Obtém o próximo estado do menu após a interação do usuário.

    int getSelectedMap() const { return selectedMap; }  /// Obtém o índice do mapa atualmente selecionado.

    ALLEGRO_BITMAP* getBackground() const { return background; } /// Obtém o ponteiro para a imagem de fundo do menu de seleção de mapas.
    float getBackgroundX() const { return backgroundX; }         /// Obtém a posição x da imagem de fundo do menu de seleção de mapas, para criar o efeito de movimento do cenário.
    ALLEGRO_FONT* getFont() const { return fontMenu; }           /// Obtém o ponteiro para a fonte utilizada no menu de seleção de mapas.
    std::string getSelectedMapName() const { return mapOptions[selectedMap]; } /// Obtém o nome do mapa atualmente selecionado.
    void mapReset() { selectedMap = 0; }                         /// Reseta a seleção do mapa para o primeiro mapa da lista.

    const Button& getLeftButton() const { return esqBtn; }      /// Getter pro botao de seleção do mapa anterior.
    const Button& getRightButton() const { return dirBtn; }     /// Getter pro botao de seleção do próximo mapa.
    const Button& getSaveButton() const { return saveBtn; }     /// Getter pro botao de salvar a seleção do mapa atual.
    const Button& getBackButton() const { return backBtn; }     /// Getter pro botao de voltar ao menu anterior.

};
#endif