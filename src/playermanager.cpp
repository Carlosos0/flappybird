#include <algorithm> 
#include <fstream>
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
        size_t sep1 = line.find(';');
        size_t sep2 = line.find(';', sep1 + 1);

        if (sep1 != std::string::npos && sep2 != std::string::npos) {
            players.push_back({
                line.substr(0, sep1),
                line.substr(sep1 + 1, sep2 - sep1 - 1),
                std::stoi(line.substr(sep2 + 1))
            });
        }
    }
}

void PlayerManager::savePlayersToFile() const {
    std::ofstream file(filename, std::ofstream::trunc); 
    for (const auto& p : players) {
        file << p.name << ";" << p.nickname << ";" << p.score << "\n";
    }
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
    players.push_back({name, nickname, 0});
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