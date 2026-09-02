#include <algorithm> 
#include <ctime>
#include <fstream>
#include <sstream>
#include "playermanager.hpp"

PlayerManager::PlayerManager() {
    loadPlayersFromFile();
}
PlayerManager::~PlayerManager() {
}
void PlayerManager::loadPlayersFromFile() {
    players.clear();
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ';')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 3) {
            Player p;
            p.name = tokens[0];
            p.nickname = tokens[1];
            p.score = std::stoi(tokens[2]);
            p.gamesPlayed = (tokens.size() > 3) ? std::stoi(tokens[3]) : 0;
            p.mapsPlayed[0] = (tokens.size() > 4) ? std::stoi(tokens[4]) : 0;
            p.mapsPlayed[1] = (tokens.size() > 5) ? std::stoi(tokens[5]) : 0;
            p.mapsPlayed[2] = (tokens.size() > 6) ? std::stoi(tokens[6]) : 0;
            p.dateRegistered = (tokens.size() > 7) ? tokens[7] : "SEMPRE!<3";
            players.push_back(p);
        }
    }
}

void PlayerManager::savePlayersToFile() const {
    std::ofstream file(filename, std::ofstream::trunc); 
    for (const auto& p : players) {
        file << p.name << ";" << p.nickname << ";" << p.score << ";" 
        << p.gamesPlayed << ";" << p.mapsPlayed[0] << ";" << p.mapsPlayed[1] << ";"
        << p.mapsPlayed[2] << ";" << p.dateRegistered << "\n";
    }
}

Player PlayerManager::getPlayerInfo(const std::string& nickname) const {
    for (const auto& p : players) {
        if (p.nickname == nickname) {
            return p;
        }
    }
    return {"", "", 0, 0, {0, 0, 0}, ""}; 
}

bool PlayerManager::nicknameExists(const std::string& nickname) const {
    for (const auto& p : players) {
        if (p.nickname == nickname) {
            return true;
        }
    }
    return false;
}

bool PlayerManager::addNewPlayer(const std::string& name, const std::string& nickname) {
    if (name.empty() || nickname.empty() || nicknameExists(nickname)) {
        return false;
    }
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateBuffer[32];
    snprintf(dateBuffer, sizeof(dateBuffer), "%02d/%02d/%04d", ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);
    Player p = {name, nickname, 0, 0, {0, 0, 0}, std::string(dateBuffer)};
    players.push_back(p);
    savePlayersToFile();
    return true;
}

void PlayerManager::updatePlayerScore(const std::string& nickname, int newScore) {
    bool updated = false;
    for (auto& p : players) {
        if (p.nickname == nickname) {
            if (newScore > p.score) {
                p.score = newScore;
                updated = true;
            }
            break;
        }
    }
    if (updated) {
        savePlayersToFile();
    }
}

std::vector<Player> PlayerManager::getRankedPlayers() const {
    std::vector<Player> sorted = players;
    std::sort(sorted.begin(), sorted.end(), [](const Player& a, const Player& b) {
        return a.score > b.score;
    });
    return sorted;
}

void PlayerManager::registerPlayer(const std::string& nickname, int mapID) {
    for (auto& p : players) {
        if (p.nickname == nickname) {
            p.gamesPlayed++;
            if (mapID >= 0 && mapID < 3) {
                p.mapsPlayed[mapID]++;
            }
            savePlayersToFile();
            return;
        }
    }
}

int PlayerManager::getHighScore(const std::string& nickname) const {
    for (const auto& p : players) {
        if (p.nickname == nickname) {
            return p.score;
        }
    }
    return 0; 
}
bool PlayerManager::deletePlayer(const std::string& nickname) {
    auto it = std::remove_if(players.begin(), players.end(),
        [&](const Player& p) {
            return p.nickname == nickname;
        });

    if (it != players.end()) {
        players.erase(it, players.end()); 
        savePlayersToFile(); 
        return true; 
    }

    return false; 
}