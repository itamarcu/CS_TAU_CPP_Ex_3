#ifndef CS_TAU_CPP_EX_2_MYFIGHTINFO_H
#define CS_TAU_CPP_EX_2_MYFIGHTINFO_H


#include "FightInfo.h"
#include "MyPoint.h"
#include "Auxiliary.h"

class MyFightInfo : public FightInfo {
public:
    MyFightInfo(int winner, const Point &position, char firstPlayerPiece, char secondPlayerPiece);

    /**
     * get position of fight
     * @return fight position
     */
    const Point &getPosition() const override;

    /**
     * get piece
     * @param player for player 1 this should be FIRST_PLAYER_CONST, for player 2 this should be SECOND_PLAYER_CONST
     * @return piece char, if player is invalid 0 will be returned
     */
    char getPiece(int player) const override;

    /**
     * get fight winner
     * @return 0 - if both lose / tie, FIRST_PLAYER_CONST - if first player wins and SECOND_PLAYER_CONST - if
     * second player wins
     */
    int getWinner() const override;

    ~MyFightInfo() override;

private:
    int winner;
    MyPoint position;
    char firstPlayerPiece;
    char secondPlayerPiece;

};


#endif //CS_TAU_CPP_EX_2_MYFIGHTINFO_H
