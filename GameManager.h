#ifndef CS_TAU_CPP_RPS_GAMEMANAGER_H
#define CS_TAU_CPP_RPS_GAMEMANAGER_H

#include <vector>
#include "GameManager.h"

#include "Game.h"
#include "BoardIO.h"
#include "PlayerAlgorithm.h"

class NewGameManager {
private:
    Game &game;
    std::unique_ptr<PlayerAlgorithm> p1_algorithm;
    std::unique_ptr<PlayerAlgorithm> p2_algorithm;
    std::vector<unique_ptr<FightInfo>> setup_fights;
public:
    explicit NewGameManager(Game &game, std::unique_ptr<PlayerAlgorithm> p1_algo,
                            std::unique_ptr<PlayerAlgorithm> p2_algo) :
            game(game), p1_algorithm(std::move(p1_algo)),
            p2_algorithm(std::move(p2_algo)), setup_fights(0) {}

    /**
     * run moves of players, alternating, until game ends
     */
    void run_game();

    /**
     * Loads piece position vector, returns success or type of failure
     * @param player 1 or 2
     * @param positions vector of positions to be used to fill the game board
     * @return a LoadBoardResult (success is good)
     */
    LoadBoardResult setup_positions(int player, std::vector<unique_ptr<PiecePosition>> &positions);

    /**
     * calls setup_positions() on both player algorithms, and writes errors if needed
     * @return true if both players loaded successfully
     */
    bool setup_both_boards();
};


#endif //CS_TAU_CPP_RPS_GAMEMANAGER_H
