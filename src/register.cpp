#include "register.hpp"

Cadastro::Cadastro(ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* a_font, PlayerManager* manager)
    : display(disp), font(a_font), playerManager(manager), nextState(MenuState::None) {
    Reset();
}

void Cadastro::Reset() {
    nome_atual.clear();
    apelido_atual.clear();
    mensagem = "Digite seu Nome e Apelido";
    digitando_nome = true;
    nextState = MenuState::None;
}

void Cadastro::ProcessEvent(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_TAB: digitando_nome = !digitando_nome; break;
            case ALLEGRO_KEY_ENTER: case ALLEGRO_KEY_PAD_ENTER:
                if (playerManager->addNewPlayer(nome_atual, apelido_atual)) {
                    mensagem = "Jogador salvo com sucesso!";
                    nextState = MenuState::GoToMainMenu;
                } else {
                    mensagem = (nome_atual.empty() || apelido_atual.empty()) ? "Erro: Campos nao podem ser vazios." : "Erro: Esse Apelido ja existe!";
                }
                break;
            case ALLEGRO_KEY_ESCAPE: nextState = MenuState::GoToMainMenu; break;
            case ALLEGRO_KEY_BACKSPACE:
                if (digitando_nome && !nome_atual.empty()) nome_atual.pop_back();
                else if (!digitando_nome && !apelido_atual.empty()) apelido_atual.pop_back();
                break;
        }
    } else if (ev.type == ALLEGRO_EVENT_KEY_CHAR && ev.keyboard.unichar >= 32) {
        if (digitando_nome && nome_atual.size() < 20) nome_atual += ev.keyboard.unichar;
        else if (!digitando_nome && apelido_atual.size() < 20) apelido_atual += ev.keyboard.unichar;
    }
}

MenuState Cadastro::getNextState() { return nextState; }
void Cadastro::Draw() { }