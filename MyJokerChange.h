#ifndef CS_TAU_CPP_EX_2_MYJOKERCHANGE_H
#define CS_TAU_CPP_EX_2_MYJOKERCHANGE_H


#include <memory>
#include "JokerChange.h"
#include "MyPoint.h"
#include "GamePiece.h"

class MyJokerChange: public JokerChange {
public:

    /**
     * MyJokerChange constructor
     * @param positionChange joker position to change to
     * @param newJokerRepresentation  new joker representation to change to
     */
    MyJokerChange(const MyPoint &positionChange, char newJokerRepresentation);

    /**
     * MyJokerChange constructor
     * @param positionChange joker position to change to
     * @param newJokerRepresentation  new joker representation to change to
     */
    MyJokerChange(const MyPoint &positionChange, GamePiece::Type newJokerRepresentation);

   /**
    * get position change of joker
    * @return Point subclass instance for new position
    */
    const Point &getJokerChangePosition() const override;

    /**
     * get new char representation of joker
     * @return new char joker representation(after change)
     */
    char getJokerNewRep() const override;

    ~MyJokerChange() override;

private:
    MyPoint positionChange;
    char jokerRepresentation;
};


#endif //CS_TAU_CPP_EX_2_MYJOKERCHANGE_H
