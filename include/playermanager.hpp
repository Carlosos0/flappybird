#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <string>
#include <vector>
#include "menu.hpp" 

class PlayerManager {
private:
    std::vector<Player> players;
    const std::string filename = "jogadores.txt";

    // Funções internas para carregar e salvar no ficheiro
    void loadPlayersFromFile();
    void savePlayersToFile() const;

public:
    PlayerManager(); 
    ~PlayerManager();

    void registerPlayer(const std::string& name, int mapID);
    Player getPlayerInfo(const std::string& nickname) const;
    bool deletePlayer(const std::string& nickname);
    bool nicknameExists(const std::string& nickname) const;
    bool addNewPlayer(const std::string& name, const std::string& nickname);
    void updatePlayerScore(const std::string& nickname, int newScore);
    int getHighScore(const std::string& nickname) const;
    std::vector<Player> getRankedPlayers() const;
};

#endif