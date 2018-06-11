#ifndef CS_TAU_CPP_RPS_BOARDIO_H
#define CS_TAU_CPP_RPS_BOARDIO_H


#include "Auxiliary.h"

#include "GameLogic.h"
#include "Game.h"
#include "PlannedMove.h"
#include <map>

/**
 * result of loading board
 */
enum LoadBoardResultType {
    UnableToOpenPath = 0,
    BadFormat = 1,
    InvalidJokerPieceType = 2,
    InvalidPieceType = 3,
    TooManyOfSamePiece = 4,
    CoordinatesOutOfBound = 5,
    TwoPiecesSamePlayerSamePosition = 6,
    NotAllFlagsWerePlaced = 7,
    BoardLoadingSuccess = 8
};

struct LoadBoardResult {
public:
    LoadBoardResultType type;
    int line_num;

    explicit LoadBoardResult(int line_number, LoadBoardResultType loadResultType) :
            type(loadResultType), line_num(line_number) {}
};

struct GameMoves {
public:
    std::vector<PlannedMove> p1_moves;
    std::vector<PlannedMove> p2_moves;

    explicit GameMoves() : p1_moves(), p2_moves() {}
};

/**
 * "static" class for handling file input and output regarding boards
 */
class BoardIO {
public:
    /**
     * store the game
     * @param game game to store
     */
    static void store_game(Game &game);

    /**
     * load file of player to board
     * @param board board to load into
     * @param player true for player 1 , false for 2
     * @return one of LoadBoardResult cases according to the success of the function
     */
    static LoadBoardResult load_board(MyBoard &board, bool player);


    static void load_moves(std::vector<PlannedMove> &moves, int player);

    /**
     * setting counts for loading board file
     * @param remainingCounts remaining counts map of pieces
     * @param remainingJokerCount remaining counts of joker
     */
    static void settingCounts(std::map<GamePiece::Type, int> &remainingCounts, int &remainingJokerCount);

};


#endif //CS_TAU_CPP_RPS_BOARDIO_H
