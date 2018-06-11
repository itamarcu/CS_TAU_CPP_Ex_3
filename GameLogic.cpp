#include <iostream>
#include "GameLogic.h"
#include "MyFightInfo.h"

/**
 * simulate a fight between two pieces and return the result
 * @param attacker attacker of fight
 * @param defender piece attacked
 * @return FightResult case matching the simulation
 */
FightResult simulate_fight(const GamePiece &attacker,
                           const GamePiece &defender) {
    //Bombs kill everyone
    if (attacker.type == GamePiece::Type::Bomb || defender.type == GamePiece::Type::Bomb)
        return BOTH_PIECES_LOST;
    //Ties are a lose-lose scenario
    if (attacker.type == defender.type)
        return BOTH_PIECES_LOST;
    //Flags are useless in combat
    if (attacker.type == GamePiece::Type::Flag)
        return DEFENDER_WON;
    if (defender.type == GamePiece::Type::Flag)
        return ATTACKER_WON;
    // Rock > Scissors > Paper
    if (attacker.type == GamePiece::Type::Rock && defender.type == GamePiece::Type::Scissors)
        return ATTACKER_WON;
    if (attacker.type == GamePiece::Type::Paper && defender.type == GamePiece::Type::Rock)
        return ATTACKER_WON;
    if (attacker.type == GamePiece::Type::Scissors && defender.type == GamePiece::Type::Paper)
        return ATTACKER_WON;

    // Paper < Scissors < Rock
    if (attacker.type == GamePiece::Type::Rock && defender.type == GamePiece::Type::Paper)
        return DEFENDER_WON;
    if (attacker.type == GamePiece::Type::Paper && defender.type == GamePiece::Type::Scissors)
        return DEFENDER_WON;
    if (attacker.type == GamePiece::Type::Scissors && defender.type == GamePiece::Type::Rock)
        return DEFENDER_WON;

    std::cout << "BUG in simulate_fight !!!";
    return FightResult::BOTH_PIECES_LOST;
}


MoveResult _make_move_part_of_planned_move(Game &game, PlannedMove &plannedMove) {
    const MyPoint &source(plannedMove.getOrigin());
    const MyPoint &destination(plannedMove.getDestination());
    int sourceRow = source.getX(), sourceColumn = source.getY(),
            destinationRow = destination.getX(), destinationColumn = destination.getY();
    if (game.board.grid[sourceRow][sourceColumn] == nullptr) {
        return TriedToMoveEmptySpace;
    }
    if (!game.board.grid[sourceRow][sourceColumn]->canMove()) {
        return TriedToMoveUnmovablePiece;
    }
    if (sourceRow == destinationRow && sourceColumn == destinationColumn) {
        return TriedToMoveIntoAlly; // tried to not move, actually, but it's the same
    }
    if (game.board.grid[sourceRow][sourceColumn]->player != game.currentPlayer) {
        return TriedToMoveEnemy;
    }
    if (game.board.grid[destinationRow][destinationColumn] == nullptr) {
        game.board.grid[destinationRow][destinationColumn] =
                game.board.grid[sourceRow][sourceColumn];
    } else {
        auto attacking_piece = game.board.grid[sourceRow][sourceColumn];
        auto defending_piece = game.board.grid[destinationRow][destinationColumn];

        if (attacking_piece->player == defending_piece->player) {
            return TriedToMoveIntoAlly;
        }
        auto result = actually_fight(
                game,
                attacking_piece,
                defending_piece,
                MyPoint(destinationRow, destinationColumn));
        int winner = 0;
        if (result == FightResult::ATTACKER_WON)
            winner = game.currentPlayer ? 1 : 2;
        else if (result == FightResult::DEFENDER_WON)
            winner = game.currentPlayer ? 2 : 1;
        game.freshFightResult = std::make_unique<MyFightInfo>(
                game.currentPlayer ?
                MyFightInfo(winner, MyPoint(destinationRow, destinationColumn, false), // TODO 1-indexing
                            GamePiece::chrFromType(defending_piece->type),
                            GamePiece::chrFromType(attacking_piece->type)) :
                MyFightInfo(winner, MyPoint(destinationRow, destinationColumn, false), // TODO 1-indexing
                            GamePiece::chrFromType(attacking_piece->type),
                            GamePiece::chrFromType(defending_piece->type)));
    }

    game.board.grid[sourceRow][sourceColumn] = nullptr;

    return SuccessfulMove;
}


MoveResult make_planned_move(Game &game, PlannedMove &plannedMove) {
    MoveResult firstResult = _make_move_part_of_planned_move(game, plannedMove);
    if (firstResult != SuccessfulMove || !plannedMove.getHasJokerChanged())
        return firstResult;

    MyPoint jokerPosition(plannedMove.getJokerPosition());
    int jx = jokerPosition.getX();
    int jy = jokerPosition.getY();
    auto joker = game.board.grid[jx][jy];
    if (joker == nullptr || !joker->isJoker || joker->player != game.currentPlayer)
        return TriedIllegalJokerChange;
    switch (plannedMove.getNewJokerType()) {
        // Only R P S B are allowed
        case GamePiece::Type::Rock:
        case GamePiece::Type::Paper:
        case GamePiece::Type::Scissors:
        case GamePiece::Type::Bomb:
            return SuccessfulMove;
        case GamePiece::Type::None:
        case GamePiece::Type::Flag:
            return TriedIllegalJokerChange;
        default:
            std::cerr << "BUG 7984132547" << std::endl;
            break;
    }
    return SuccessfulMove;
}

FightResult actually_fight(Game &game, std::shared_ptr<GamePiece> attacker,
                           std::shared_ptr<GamePiece> defender, Point &&position) {
    int r = position.getX();
    int c = position.getY();
    auto fightResult = simulate_fight(*attacker, *defender);
    switch (fightResult) {
        case ATTACKER_WON:
            game.board.grid[r][c] = attacker;
            break;
        case DEFENDER_WON:
            game.board.grid[r][c] = defender;
            break;
        case BOTH_PIECES_LOST:
            game.board.grid[r][c] = nullptr;
            break;
        default:
            print_line("ERROR in actually_fight because of weird fight result");
    }

    return fightResult;
}
