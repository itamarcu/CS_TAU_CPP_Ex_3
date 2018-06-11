#ifndef CS_TAU_CPP_EX_2_MYPIECEPOSITION_H
#define CS_TAU_CPP_EX_2_MYPIECEPOSITION_H


#include "PiecePosition.h"
#include "MyPoint.h"
#define NON_JOKER_REPR_DEFAULT 0
class MyPiecePosition : public PiecePosition {
public:
    /**
     * a constructor for a piece
     * @param piece the piece char
     * @param jokerRep joker representation, if it is a joker, if not please use `NON_JOKER_REPR_DEFAULT`
     * @param position the point in which the piece sits
     */
    MyPiecePosition(char piece, char jokerRep, const MyPoint &position);

    /**
     * get the position of the piece
     * @return the position of the piece as a point subclass
     */
    const Point &getPosition() const override;

    /**
     * the piece char representation of the piece
     * @return piece char
     * @warning this method shouldn't be used to know joker representation, for that it will return joker char and you'll have
     * to use getJokerRep to know the representation of a joker
     */
    char getPiece() const override;

    /**
     * @important use only if the piece is joker
     * @return joker representation
     */
    char getJokerRep() const override;

    ~MyPiecePosition() override;
private:
    char piece;
    char jokerRep;
    MyPoint position;
};


#endif //CS_TAU_CPP_EX_2_MYPIECEPOSITION_H
