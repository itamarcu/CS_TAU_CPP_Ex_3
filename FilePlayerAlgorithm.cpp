#include "FilePlayerAlgorithm.h"
#include "MyMove.h"
#include "MyJokerChange.h"
#include "MyPiecePosition.h"
#include "BoardIO.h"
#include <iostream>

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    this->player = player;
    MyBoard board;
    auto result = BoardIO::load_board(board, player == FIRST_PLAYER_CONST);
    if (result.type == BoardLoadingSuccess) {
        //iterate over board
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (board.grid[i][j]) {
                    // piece in board
                    MyPoint pointOnBoard(i, j);
                    std::shared_ptr<GamePiece> gamePiece = board.grid[i][j];
                    char type = GamePiece::chrFromType(gamePiece->getType());
                    char jokerChar = gamePiece->isJoker ? type : (char) NON_JOKER_REPR_DEFAULT;
                    unique_ptr<PiecePosition> piece = std::make_unique<MyPiecePosition>(
                            gamePiece->isJoker ? JOKER_CHAR : type, jokerChar, pointOnBoard);
                    vectorToFill.push_back(std::move(piece));
                }
            }
        }
    } else {
        std::cout << "Invalid board-load for player " << player << ": errornum " << result.type << " in line "
                  << result.line_num << std::endl;
    }
}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {
    //Empty on purpose
    (void) b;
    (void) fights;
}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
    //Empty on purpose
    (void) move;
}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    //Empty on purpose
    (void) fightInfo;
}

unique_ptr<Move> FilePlayerAlgorithm::getMove() {
    if (alreadyGotMovementPartOfMove) {
        alreadyGotJokerPartOfMove = false;
        movesList.pop_front();
    }
    if (movesList.empty())
        return nullptr; // no more moves, so send invalid move

    alreadyGotMovementPartOfMove = true;

    std::shared_ptr<PlannedMove> plannedMove = movesList.front();
    unique_ptr<Move> move = std::make_unique<MyMove>(plannedMove->getOrigin(), plannedMove->getDestination());

    return move;
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange() {
    if (alreadyGotJokerPartOfMove) {
        alreadyGotMovementPartOfMove = false;
        movesList.pop_front();
    }
    if (movesList.empty())
        return nullptr; // no more moves

    alreadyGotJokerPartOfMove = true;

    std::shared_ptr<PlannedMove> plannedMove = movesList.front();
    if (plannedMove->getHasJokerChanged()) {
        unique_ptr<JokerChange> jokerChange = std::make_unique<MyJokerChange>(plannedMove->getJokerPosition(),
                                                                              plannedMove->getNewJokerType());
        return jokerChange;
    } else
        return nullptr; // no joker change
}

FilePlayerAlgorithm::~FilePlayerAlgorithm() = default;

FilePlayerAlgorithm::FilePlayerAlgorithm(int player) : player(player) {
    alreadyGotJokerPartOfMove = false;
    alreadyGotMovementPartOfMove = false;
    std::vector<PlannedMove> playersMoves;
    BoardIO::load_moves(playersMoves, player);
    for (auto &playersMove : playersMoves) {
        std::shared_ptr<PlannedMove> ptr = std::make_shared<PlannedMove>(playersMove);
        movesList.push_back(ptr);
    }


}
