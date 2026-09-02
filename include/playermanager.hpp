/**
 * @file playermanager.hpp
 * @brief Implementação da classe PlayerManager, responsável pelo cadastro, ranking e gerenciamento
 * de jogadores.
 */
#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <string>
#include <vector>
#include "menu.hpp" 

/**
 * @class PlayerManager
 * @brief Gerencia cadastro, ranking e estatísticas de jogadores, sincronizando
 * com um arquivo de texto (.txt).
 */

class PlayerManager {
private:

    std::vector<Player> players;                    /// Vetor de armazenamento de jogadores cadastrados.
    const std::string filename = "jogadores.txt";   /// Nome do arquivo de sincronização/salvamento dos jogadores.

    /// @brief Carrega a lista de jogadores a partir do arquivo de salvamento.
    void loadPlayersFromFile();

    /// @brief Grava a lista atual de jogadores no arquivo de salvamento.
    void savePlayersToFile() const;

public:

    /// @brief Construtor que carrega a lista de jogadores existentes.
    PlayerManager(); 

    /// @brief Destrutor padrão.
    ~PlayerManager();

    /**
     * @brief Registra uma partida jogada por um jogador em um mapa específico.
     * @param name Apelido do jogador.
     * @param mapID Índice do mapa jogado.
     */
    void registerPlayer(const std::string& name, int mapID);

    /**
     * @brief Recupera os dados de um jogador pelo apelido.
     * @param nickname Apelido do jogador buscado.
     * @return Cópia dos dados do jogador, ou vazio se não encontrado.
     */
    Player getPlayerInfo(const std::string& nickname) const;

    /**
     * @brief Remove um jogador cadastrado.
     * @param nickname Apelido do jogador buscado.
     * @return true se o jogador foi encontrado e removido.
     */
    bool deletePlayer(const std::string& nickname);

    /**
     * @brief Verifica se um apelido está cadastrado.
     * @param nickname Apelido do jogador buscado.
     * @return true se o apelido já está cadastrado, false em caso contrário.
     */
    bool nicknameExists(const std::string& nickname) const;

    /**
     * @brief Cadastra um novo jogador, se o nome e apelido forem válidos.
     * @param name Nome do jogador.
     * @param nickname Apelido do jogador.
     * @return true se o cadastro teve sucesso, false em caso contrário.
     */
    bool addNewPlayer(const std::string& name, const std::string& nickname);

    /**
     * @brief Atualiza a pontuação máxima do jogador, se a nova pontuação
     * for maior do que a atualmente cadastrada.
     * @param nickname Apelido do jogador.
     * @param newScore Novo recorde a ser cadastrado.
     */
    void updatePlayerScore(const std::string& nickname, int newScore);

    /**
     * @brief Getter para o recorde de um jogador.
     * @param nickname Apelido do jogador buscado.
     * @return Recorde do jogador.
     */
    int getHighScore(const std::string& nickname) const;


    /**
     * @return Lista dos jogadores cadastrados, ordenados por pontuação decrescente.
     */
    std::vector<Player> getRankedPlayers() const;
};

#endif