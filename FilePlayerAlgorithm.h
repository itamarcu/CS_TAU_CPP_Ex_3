#ifndef CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H
#define CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H


#include <list>
#include "PlayerAlgorithm.h"
#include "PlannedMove.h"
#include "MyBoard.h"


class FilePlayerAlgorithm : public PlayerAlgorithm {
private:
    bool alreadyGotJokerPartOfMove;
    bool alreadyGotMovementPartOfMove;
    int player; // 1 or 2

    std::list<std::shared_ptr<PlannedMove>> movesList;
public:
    /**
     * initialize file player algorithm using player, this performs load from matching default file
     * as described in EX1
     * @param player
     */
    explicit FilePlayerAlgorithm(int player);

    /**
     * initialize player positions
     * @param player player should be equal to ivar player
     * @param vectorToFill vector to fill
     */
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) override;

    /**
     * Does nothing because the file player is stupid
     */
    void notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) override;


    /**
     * Does nothing because the file player is dumb
     */
    void notifyOnOpponentMove(const Move &move) override;

    /**
     * Does nothing because the file player is an imbecile
     */
    void notifyFightResult(const FightInfo &fightInfo) override;

    /**
     * get next move
     * @return next move
     */
    unique_ptr<Move> getMove() override;

    /**
     * get joker change
     * @return joker change, nullptr if no change
     */
    unique_ptr<JokerChange> getJokerChange() override;

    ~FilePlayerAlgorithm() override;
};


#endif //CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H
