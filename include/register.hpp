#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "menu.hpp"
#include "playermanager.hpp" 

class Cadastro : public Menu {

private:

    bool digitando_nome;

    std::string nome_atual;
    std::string apelido_atual;
    std::string mensagem;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;
    PlayerManager* playerManager;

    MenuState nextState;

public:

    Cadastro(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, PlayerManager* manager);

    void ProcessEvent(const ALLEGRO_EVENT& event) override;
    void Draw() override;
    void Reset() override;

    MenuState getNextState() override;

    const std::string& getNomeAtual() const { return nome_atual; }
    const std::string& getApelidoAtual() const { return apelido_atual; }
    const std::string& getMensagem() const { return mensagem; }
    bool isDigitandoNome() const { return digitando_nome; }
    ALLEGRO_FONT* getFont() const { return font; }
};

#endif