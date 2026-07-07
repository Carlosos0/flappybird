#include "graphloader.hpp"

graphloader::graphloader(){
    display = NULL;
}

graphloader::~graphloader(){}

bool graphloader::InitDisplay(ALLEGRO_DISPLAY* display){
    if (!display)
    {
        return false;
    }
    this->display = display;
    return true;
}

ALLEGRO_BITMAP* graphloader::ScaleBitmap(const char* filename, float dw, float dh, ALLEGRO_DISPLAY* display){
    ALLEGRO_BITMAP* originalBitmap = al_load_bitmap(filename);
    if (!originalBitmap) {
        return nullptr;
    }

    ALLEGRO_BITMAP* scaledBitmap = al_create_bitmap(dw, dh);
    if (!scaledBitmap){
        al_destroy_bitmap(originalBitmap);
        return nullptr;
    }

    al_set_target_bitmap(scaledBitmap);

    al_draw_scaled_bitmap(
        originalBitmap,
        0, 0,
        al_get_bitmap_width(originalBitmap),
        al_get_bitmap_height(originalBitmap),
        0, 0,
        dw, dh,
        0);

    al_set_target_bitmap(al_get_backbuffer(display));
    al_destroy_bitmap(originalBitmap);

    return scaledBitmap;
}

void graphloader::Clear(){
    al_clear_to_color(al_map_rgb(255, 255, 255));
}

void graphloader::Update(){
    al_flip_display();
}

void graphloader::DrawBG(ALLEGRO_BITMAP* background){
    if (!background)
    {
        return;
    }
    al_draw_bitmap(background, 0, 0, 0);
}

void graphloader::DrawBird(const bird& brd){
   ALLEGRO_BITMAP* brdImg = brd.getImage();
   if (brdImg)
   {
    vetor brdPos = brd.getPosition();
    float brdRot = brd.getRotation();

    vetor center = vetor(brd.getWidth()/2.0f, brd.getHeight()/2.0f);
    vetor centerPos = brdPos + center;

    al_draw_rotated_bitmap(
        brdImg, 
        center.x, center.y, 
        centerPos.x, centerPos.y, 
        brdRot, 
        0); 
   }
}

void graphloader::DrawPipe(const Pipe& obj){
    ALLEGRO_BITMAP* pipeImg = obj.getImage();
    if (pipeImg)
    {
        vetor pipePos = obj.getPosition();
        int flag = 0;

        if (!obj.IsBottom())
        {
            flag = ALLEGRO_FLIP_VERTICAL;
        }
        
        al_draw_bitmap(pipeImg, pipePos.x, pipePos.y, flag);
    }
}

void graphloader::DrawPipePair(const std::vector<std::unique_ptr<doublepipes>>& pipes){
    for (const auto& pipe : pipes) {
        DrawPipe(pipe->getBottom());
        DrawPipe(pipe->getTop());
    }
}

void graphloader::DrawFloor(const floor& obj) {
    ALLEGRO_BITMAP* image = obj.getImage();
    if (image) {
        float bgX = obj.getBackgroundX(); 
        
        float floorY = obj.getPosition().y; 
        int imageWidth = al_get_bitmap_width(image);
        al_draw_bitmap(image, bgX, floorY, 0);
        al_draw_bitmap(image, bgX + imageWidth, floorY, 0);
    }
}

void graphloader::DrawButton(const Button& button, ALLEGRO_FONT* font) {
    // Cores
    ALLEGRO_COLOR mainColor      = al_map_rgb(50, 150, 70); 
    ALLEGRO_COLOR highlightColor = al_map_rgb(39, 105, 65);
    ALLEGRO_COLOR shadowColor    = al_map_rgb(39, 53, 55);
    ALLEGRO_COLOR textColor      = al_map_rgb(255, 255, 255);
    int shadowThickness = 4;

    al_draw_filled_rectangle(button.x, button.y, button.x + button.width, button.y + button.height, mainColor);
    al_draw_filled_rectangle(button.x, button.y + button.height - shadowThickness, button.x + button.width, button.y + button.height, shadowColor);
    al_draw_filled_rectangle(button.x + button.width - shadowThickness, button.y, button.x + button.width, button.y + button.height, shadowColor);
    al_draw_line(button.x, button.y, button.x + button.width, button.y, highlightColor, 2.0);
    al_draw_line(button.x, button.y, button.x, button.y + button.height, highlightColor, 2.0);

    if (font) {
        al_draw_text(font, textColor, 
                     button.x + button.width / 2, 
                     button.y + button.height / 2 - al_get_font_ascent(font) / 2, 
                     ALLEGRO_ALIGN_CENTER, 
                     button.text);
    }
}



void graphloader::DrawMenu(const PrincipalMenu& menu) {
 
    ALLEGRO_BITMAP* bg = menu.getBackground();
    if (bg) {
        float bgX = menu.getBackgroundX(); 
        al_draw_bitmap(bg, bgX, 0, 0);
        al_draw_bitmap(bg, bgX + al_get_bitmap_width(bg), 0, 0);
    }


    ALLEGRO_FONT* titleFont = menu.getFontTitle();
    if (titleFont) {
        ALLEGRO_COLOR titleColor = al_map_rgb(255, 255, 0); 
        ALLEGRO_COLOR shadowColor = al_map_rgb(255, 200, 12); 
        
    
        al_draw_text(titleFont, shadowColor, 800 / 2 + 4, 80 + 4, ALLEGRO_ALIGN_CENTER, "FLAPPY BIRD");
        al_draw_text(titleFont, titleColor, 800 / 2, 80, ALLEGRO_ALIGN_CENTER, "FLAPPY BIRD");
    }
    const std::vector<Button>& buttons = menu.getButtons();
    ALLEGRO_FONT* buttonFont = menu.getFont();

    for (const Button& btn : buttons) {
        DrawButton(btn, buttonFont); 
    }
}
void graphloader::DrawGameOverMenu(const GameOverMenu& menu, ALLEGRO_FONT* font, int currentScore, int bestScore, bool newRecord) {
    ALLEGRO_FONT* font2 = menu.getFont();
    float panelX = 200, panelY = 150, panelW = 400, panelH = 220; 
    ALLEGRO_COLOR panelColor = al_map_rgba(40, 40, 40, 200);      

    al_draw_filled_rectangle(panelX, panelY, panelX + panelW, panelY + panelH, panelColor);
    al_draw_rectangle(panelX, panelY, panelX + panelW, panelY + panelH, al_map_rgb(255,255,255), 2); 
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 180, ALLEGRO_ALIGN_CENTER, "FIM DE JOGO!");
    al_draw_textf(font2, al_map_rgb(255, 255, 255), 400, 240, ALLEGRO_ALIGN_CENTER, "PONTUAÇÃO: %d", currentScore);
    al_draw_textf(font2, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTER, "MELHOR PONTUAÇÃO: %d", bestScore);
    
    if (newRecord) {
        al_draw_text(font2, al_map_rgb(255, 215, 0), 400, 320, ALLEGRO_ALIGN_CENTER, "NOVO RECORDE!");
    }
    
    
    
    const std::vector<Button>& buttons = menu.getButtons();
    ALLEGRO_FONT* buttonFont = menu.getFont();

    for (const Button& btn : buttons) {
        DrawButton(btn, buttonFont); 
    }
}


void graphloader::DrawRegisterMenu(const Cadastro& menu, ALLEGRO_FONT* font) {
    
    const std::string& nome_atual = menu.getNomeAtual();
    const std::string& apelido_atual = menu.getApelidoAtual();
    const std::string& mensagem = menu.getMensagem();
    bool digitando_nome = menu.isDigitandoNome();
    
    ALLEGRO_COLOR cor_fundo = al_map_rgb(10, 150, 200);
    al_clear_to_color(cor_fundo);
    float panel_w = 600, panel_h = 450;
    float panel_x = (800 - panel_w) / 2;
    float panel_y = (600 - panel_h) / 2;
    al_draw_filled_rounded_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h, 8, 8, al_map_rgba(0,0,0,100));
    al_draw_rounded_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h, 8, 8, al_map_rgb(100,100,120), 2);


    al_draw_text(font, al_map_rgb(255, 255, 255), 400, panel_y + 50, ALLEGRO_ALIGN_CENTER, "CADASTRO DE JOGADOR");

 
    ALLEGRO_COLOR cor_mensagem = (mensagem.find("Erro") != std::string::npos) ? al_map_rgb(255,100,100) : al_map_rgb(100,255,100);
    al_draw_text(font, cor_mensagem, 400, 200, ALLEGRO_ALIGN_CENTER, mensagem.c_str());

    // CAMPO NOME
    al_draw_text(font, al_map_rgb(220, 220, 220), 160, 290, ALLEGRO_ALIGN_LEFT, "Nome:"); // TITULO NOME
    al_draw_filled_rectangle(300, 280, 640, 320, al_map_rgb(30,40,70)); // CAIXA NOME
    al_draw_text(font, al_map_rgb(255,255,255), 470, 290, ALLEGRO_ALIGN_CENTER, nome_atual.c_str()); // TEXTO NOME
    if (digitando_nome) al_draw_rectangle(300, 280, 640, 320, al_map_rgb(255,200,0), 2); // DESTAQUE NOME

    // CAMPO APELIDO
    al_draw_text(font, al_map_rgb(220, 220, 220), 160, 370, ALLEGRO_ALIGN_LEFT, "Apelido:");
    al_draw_filled_rectangle(300, 360, 640, 400, al_map_rgb(30,40,70));
    al_draw_text(font, al_map_rgb(255,255,255), 470, 370, ALLEGRO_ALIGN_CENTER, apelido_atual.c_str());
    if (!digitando_nome) al_draw_rectangle(300, 360, 640, 400, al_map_rgb(255,200,0), 2);

    al_draw_filled_rectangle(136, 448, 196, 468, al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(0, 0, 0), 140, 450, ALLEGRO_ALIGN_LEFT, "TAB");
    al_draw_text(font, al_map_rgb(150,150,150), 270, 450, ALLEGRO_ALIGN_CENTER, "Alternar");

    al_draw_filled_rectangle(136, 478, 230, 498, al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(0, 0, 0), 141, 480, ALLEGRO_ALIGN_LEFT, "ENTER");
    al_draw_text(font, al_map_rgb(150,150,150), 290, 480, ALLEGRO_ALIGN_CENTER, "SALVAR");

    al_draw_filled_rectangle(394, 448, 456, 468, al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(0,0,0), 400, 450, ALLEGRO_ALIGN_LEFT, "ESC");
    al_draw_text(font, al_map_rgb(150,150,150), 470, 450, ALLEGRO_ALIGN_LEFT, "VOLTAR");
}

void graphloader::DrawListPlayersMenu(const ListPlayers& menu) {

    ALLEGRO_FONT* font = menu.getFont();
    const auto& players = menu.getPlayers();
    int scroll = menu.getScrollOffset();

    ALLEGRO_COLOR cor_fundo = al_map_rgb(10, 20, 50);
    ALLEGRO_COLOR cor_painel = al_map_rgba(0, 0, 0, 100);
    ALLEGRO_COLOR cor_borda = al_map_rgb(100, 100, 120);
    ALLEGRO_COLOR cor_titulo = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR cor_sombra = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR cor_ouro = al_map_rgb(255, 215, 0);
    ALLEGRO_COLOR cor_prata = al_map_rgb(192, 192, 192);
    ALLEGRO_COLOR cor_bronze = al_map_rgb(205, 127, 50);
    ALLEGRO_COLOR cor_texto = al_map_rgb(220, 220, 220);

    al_clear_to_color(cor_fundo);
    float panel_w = 700, panel_h = 500;
    float panel_x = (800 - panel_w) / 2;
    float panel_y = (600 - panel_h) / 2;
    al_draw_filled_rounded_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h, 8, 8, cor_painel);
    al_draw_rounded_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h, 8, 8, cor_borda, 2);

  
    float title_x = 400;
    float title_y = panel_y + 30;
    al_draw_text(font, cor_sombra, title_x + 2, title_y + 2, ALLEGRO_ALIGN_CENTER, "RANKING DE JOGADORES");
    al_draw_text(font, cor_titulo, title_x, title_y, ALLEGRO_ALIGN_CENTER, "RANKING DE JOGADORES");

 
    float list_y = title_y + 60;
    al_draw_text(font, cor_borda, panel_x + 50, list_y, ALLEGRO_ALIGN_LEFT, "POS");
    al_draw_text(font, cor_borda, panel_x + 150, list_y, ALLEGRO_ALIGN_LEFT, "JOGADOR");
    al_draw_text(font, cor_borda, panel_x + 550, list_y, ALLEGRO_ALIGN_RIGHT, "PONTOS");
    al_draw_line(panel_x + 30, list_y + 30, panel_x + panel_w - 30, list_y + 30, cor_borda, 1);

    if (players.empty()) {
        al_draw_text(font, cor_texto, title_x, 300, ALLEGRO_ALIGN_CENTER, "Nenhum jogador cadastrado.");
    } else {
        int items_por_tela = 10;
        for (int i = 0; i < items_por_tela; ++i) {
            int player_index = i + scroll;
            if (player_index >= static_cast<int>(players.size())) break;

            const auto& p = players[player_index];
            float item_y = list_y + 50 + (i * 35);
            
            ALLEGRO_COLOR cor_pos = cor_texto;
            if (player_index == 0) cor_pos = cor_ouro;
            else if (player_index == 1) cor_pos = cor_prata;
            else if (player_index == 2) cor_pos = cor_bronze;

            std::string pos_text = std::to_string(player_index + 1) + ".";
            std::string player_text = p.name + " (" + p.nickname + ")";
            al_draw_text(font, cor_pos, panel_x + 50, item_y, ALLEGRO_ALIGN_LEFT, pos_text.c_str());
            al_draw_text(font, cor_texto, panel_x + 150, item_y, ALLEGRO_ALIGN_LEFT, player_text.c_str());
            al_draw_textf(font, cor_pos, panel_x + 550, item_y, ALLEGRO_ALIGN_RIGHT, "%d", p.score);
        }
    }

    float instrucoes_y = panel_y + panel_h - 30;
    al_draw_text(font, cor_borda, title_x, instrucoes_y + 42, ALLEGRO_ALIGN_CENTER, "SETAS Rolar | ESC Voltar");
}

void graphloader::DrawNicknameInputMenu(const NicknameInput& menu, ALLEGRO_FONT* secondFont) {

    ALLEGRO_FONT* font = menu.getFont();
    std::string nickname = menu.getNickname();
    bool hasError = menu.hasError();
    std::string errorMsg = menu.getErrorMessage();

    al_clear_to_color(al_map_rgb(10, 150, 200));

    float panel_w = 500, panel_h = 250;
    float panel_x = (800 - panel_w) / 2;
    float panel_y = (600 - panel_h) / 2;

    // Draw panel background and border
    al_draw_filled_rounded_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h + 50, 8, 8, al_map_rgba(0,0,0,100));
    al_draw_rounded_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h + 50, 8, 8, al_map_rgb(100,100,120), 2);
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, panel_y + 40, ALLEGRO_ALIGN_CENTER, "Digite seu Apelido");
    float input_x = panel_x + 50, input_y = panel_y + 100;
    float input_w = 400, input_h = 40;

    // INPUT BOX
    al_draw_filled_rectangle(input_x, input_y, input_x + input_w, input_y + input_h, al_map_rgb(30,40,70));
    al_draw_rectangle(input_x, input_y, input_x + input_w, input_y + input_h, al_map_rgb(255,200,0), 2);
    al_draw_text(font, al_map_rgb(255,255,255), input_x + 10, input_y + 12, ALLEGRO_ALIGN_LEFT, nickname.c_str());
    

    if (hasError) {
        al_draw_text(font, al_map_rgb(255, 100, 100), 400, input_y + 50, ALLEGRO_ALIGN_CENTER, errorMsg.c_str());
    }

    // ENTER BUTTON
    al_draw_filled_rectangle(270, panel_y + panel_h - 50, 364, panel_y + panel_h - 30, al_map_rgb(255, 255, 255));
    al_draw_text(secondFont, al_map_rgb(0, 0, 0), 275, panel_y + panel_h - 48, ALLEGRO_ALIGN_LEFT, "ENTER");
    al_draw_text(secondFont, al_map_rgb(150,150,150), 375, panel_y + panel_h - 48, ALLEGRO_ALIGN_LEFT, "CONFIRMAR");

    // ESC BUTTON
    al_draw_filled_rectangle(270, panel_y + panel_h - 15, 330, panel_y + panel_h + 5, al_map_rgb(255, 255, 255));
    al_draw_text(secondFont, al_map_rgb(0, 0, 0), 275, panel_y + panel_h - 13, ALLEGRO_ALIGN_LEFT, "ESC");
    al_draw_text(secondFont, al_map_rgb(150,150,150), 340, panel_y + panel_h - 13, ALLEGRO_ALIGN_LEFT, "VOLTAR");
}

void graphloader::DrawDeleteMenu(const DeleteMenu& menu) {
    al_clear_to_color(al_map_rgb(10, 20, 50));
    ALLEGRO_FONT* font = menu.getFont();

    al_draw_text(font, al_map_rgb(255,255,255), 400, 50, ALLEGRO_ALIGN_CENTER, "APAGAR JOGADOR");
    const auto& players = menu.getPlayers();
    if (players.empty()) {
        al_draw_text(font, al_map_rgb(200,200,200), 400, 300, ALLEGRO_ALIGN_CENTER, "Nenhum jogador para apagar.");
    } else {
        for (size_t i = 0; i < players.size(); ++i) {
            float item_y = 150 + (i * 40);
            std::string text = players[i].name + " (" + players[i].nickname + ")";
            al_draw_text(font, al_map_rgb(220,220,220), 100, item_y + 10, ALLEGRO_ALIGN_LEFT, text.c_str());

            Button deleteBtn = {600, item_y, 100, 40, "Apagar", MenuState::None};
            if (static_cast<int>(i) == menu.getHighlightedIndex()) {
                al_draw_filled_rectangle(deleteBtn.x, deleteBtn.y, deleteBtn.x + deleteBtn.width, deleteBtn.y + deleteBtn.height, al_map_rgb(200, 20, 20));
            } else {
                al_draw_filled_rectangle(deleteBtn.x, deleteBtn.y, deleteBtn.x + deleteBtn.width, deleteBtn.y + deleteBtn.height, al_map_rgb(120, 0, 0));
            }
            al_draw_text(font, al_map_rgb(255,255,255), deleteBtn.x + 50, deleteBtn.y + 10, ALLEGRO_ALIGN_CENTER, deleteBtn.text);
        }
    }
    
    
    if (menu.isConfirming()) {
        al_draw_filled_rectangle(0, 0, 800, 600, al_map_rgba(0, 0, 0, 180));
        
    
        float panel_w = 400, panel_h = 200;
        float panel_x = (800 - panel_w) / 2;
        float panel_y = (600 - panel_h) / 2;
        al_draw_filled_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h, al_map_rgb(20, 30, 60));
        al_draw_rectangle(panel_x, panel_y, panel_x + panel_w, panel_y + panel_h, al_map_rgb(150,150,150), 2);
        
        al_draw_text(font, al_map_rgb(255,255,255), 400, panel_y + 50, ALLEGRO_ALIGN_CENTER, "Tem a certeza?");
        DrawButton(menu.getConfirmButton(), font);
        DrawButton(menu.getCancelButton(), font);
    }

    al_draw_text(font, al_map_rgb(150,150,150), 400, 570, ALLEGRO_ALIGN_CENTER, "Pressione ESC para voltar");
}

void graphloader::DrawExitConfirmMenu(const ExitConfirmMenu& menu) {
    ALLEGRO_FONT* font = menu.getFont();
    al_draw_filled_rectangle(0, 0, 800, 600, al_map_rgba(0, 0, 0, 150));
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Deseja sair?");
    DrawButton({300.0f, 300.0f, 200.0f, 50.0f, "SAIR", MenuState::Exit}, font);
    DrawButton({300.0f, 350.0f, 200.0f, 50.0f, "VOLTAR", MenuState::GoToMainMenu}, font);
}

void graphloader::DrawLoggedMenu(const LoggedMenu& menu, const std::string& lgNickname) {
    ALLEGRO_BITMAP* background = menu.getBackground();
    if (background) {
        float bgX = menu.getBackgroundX(); 
        al_draw_bitmap(background, bgX, 0, 0);
        al_draw_bitmap(background, bgX + al_get_bitmap_width(background), 0, 0);
    }

    ALLEGRO_FONT* fontMenu = menu.getFont();
    if (fontMenu) {
        ALLEGRO_COLOR titleColor = al_map_rgb(255, 255, 0); 
        ALLEGRO_COLOR shadowColor = al_map_rgb(255, 200, 12);
        std::string welcomeText = "Bem-vindo(a), " + lgNickname + "!";
        al_draw_text(fontMenu, shadowColor, 800 / 2 + 4, 80 + 4, ALLEGRO_ALIGN_CENTER, welcomeText.c_str());
        al_draw_text(fontMenu, titleColor, 800 / 2, 80, ALLEGRO_ALIGN_CENTER, welcomeText.c_str());
    }

    const std::vector<Button>& buttons = menu.getButtons();
    for (const Button& btn : buttons) {
        DrawButton(btn, fontMenu); 
    }
}

void graphloader::DrawMapMenu(const MapMenu& menu, ALLEGRO_FONT* font) {
    ALLEGRO_BITMAP* background = menu.getBackground();

    if (background) {
        float bgX = menu.getBackgroundX();
        al_draw_bitmap(background, bgX, 0, 0);
        al_draw_bitmap(background, bgX + al_get_bitmap_width(background), 0, 0);
    }
    
    al_draw_text(font, al_map_rgb(255,255,255), 400, 50, ALLEGRO_ALIGN_CENTER, "SELECIONE O MAPA");
    DrawButton(menu.getLeftButton(), font);
    DrawButton(menu.getRightButton(), font);

    al_draw_filled_rectangle(280, 250, 520, 300, al_map_rgb(30, 30, 60));
    al_draw_rectangle(280, 250, 520, 300, al_map_rgb(150,150,150), 2);

    std::string selectedMapName = menu.getSelectedMapName();
    al_draw_text(font, al_map_rgb(255,255,255), 400, 270, ALLEGRO_ALIGN_CENTER, selectedMapName.c_str());

    DrawButton(menu.getSaveButton(), font);
    DrawButton(menu.getBackButton(), font);
}

void graphloader::DrawStatusMenu(const StatusMenu& menu, const Player& player) {
    al_clear_to_color(al_map_rgb(10, 20, 50));
    ALLEGRO_FONT* font = menu.getFont();

    al_draw_filled_rectangle(150, 100, 650, 400, al_map_rgb(30, 30, 60));
    al_draw_rounded_rectangle(150, 100, 650, 400, 8, 8, al_map_rgb(150,150,150), 2);

    std::string title = player.nickname;
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 120, ALLEGRO_ALIGN_CENTER, title.c_str());

    std::string MapsPlayed[] = {"Terra", "Lua", "Marte"};
    int maxPlays = -1;
    std::string mostPlayedMap = "N/A";
    for (int i = 0; i < 3; ++i) {
        if (player.mapsPlayed[i] > maxPlays && player.mapsPlayed[i] > 0) {
            maxPlays = player.mapsPlayed[i];
            mostPlayedMap = MapsPlayed[i];
        }
    }

    al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 180, ALLEGRO_ALIGN_CENTER, "Jogos Jogados: %d", player.gamesPlayed);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 220, ALLEGRO_ALIGN_CENTER, "Mapa Mais Jogados: %s", mostPlayedMap.c_str());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 260, ALLEGRO_ALIGN_CENTER, "Melhor Pontuação: %d", player.score);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Usuário desde: %s", player.dateRegistered.c_str());

    DrawButton(menu.getBtnVoltar(), font);
}