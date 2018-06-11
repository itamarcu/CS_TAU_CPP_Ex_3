#ifndef CS_TAU_CPP_RPS_BGAME_H
#define CS_TAU_CPP_RPS_BGAME_H


#include "MyBoard.h"
#include "FightInfo.h"

enum MoveResult { // Can't be in GameLogic due to circular dependency
    SuccessfulMove = 0,
    TriedToMoveEmptySpace = 1,
    TriedToMoveUnmovablePiece = 2,
    TriedToMoveOutOfBorders = 3,
    TriedToMoveIntoAlly = 4,
    TriedToMoveEnemy = 5,
    TriedIllegalJokerChange = 6
};

enum GameWinner {
    GAME_NOT_ENDED = 3,
    PLAYER_1_VICTORY = 1,
    PLAYER_2_VICTORY = 2,
    TIE = 0
};

class Game {
    // Fields
private:
    GameWinner gameWinner;
    std::string gameEndReason;
public:
    /**
    * board of game
    */
    MyBoard board;

    /**
     * true = Player 1, false = Player 2
     */
    bool currentPlayer;

    std::unique_ptr<FightInfo> freshFightResult;

    //MARK: Constructors
public:
    /**
     * initialize game with default parameters
     */
    explicit Game() : gameWinner(GAME_NOT_ENDED),
                      gameEndReason("Game did not end yet"),
                      board(),
                      currentPlayer(true),
                      freshFightResult(nullptr) {}

    //MARK: Functions
public:
    /**
     * set a game result
     * @param gameWinner game winner to set
     * @param gameEndReason reason for ending
     */
    void endGame(GameWinner gameWinner, std::string gameEndReason);

    /**
     * @return true if a player has lost through inability to move
     * (changes gameWinner and gameEndReason)
     */
    bool checkWin();

    //MARK: Getters:
public:
    GameWinner getGameWinner() const;

    std::string getGameEndReason() const;
};


#endif //CS_TAU_CPP_RPS_BGAME_H
