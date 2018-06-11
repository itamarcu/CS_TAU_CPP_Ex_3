#ifndef CS_TAU_CPP_RPS_GAMELOGIC_H
#define CS_TAU_CPP_RPS_GAMELOGIC_H

#include "Game.h"
#include "PlannedMove.h"

enum FightResult {
    ATTACKER_WON, DEFENDER_WON, BOTH_PIECES_LOST
};


/**
 * Makes a move on the board of the game
 * @param game the game
 * @param plannedMove the move to make on the board
 * @return the move result, being
 * one of the cases in the MoveResult Enum
 */
MoveResult make_planned_move(Game &game, PlannedMove &plannedMove);

/**
 * fight between pieces if needed
 * @warning public because needed elsewhere
 * @param game game to play in
 * @param attacker attacker of fight
 * @param defender defender fight
 * @param position position the pieces fight in
 * @return FightResult case
 */
FightResult actually_fight(Game &game, std::shared_ptr<GamePiece> attacker,
                          std::shared_ptr<GamePiece> defender, Point &&position);

#endif //CS_TAU_CPP_RPS_GAMELOGIC_H
