#include "MyJokerChange.h"

const Point &MyJokerChange::getJokerChangePosition() const {
    return positionChange;
}

char MyJokerChange::getJokerNewRep() const {
    return jokerRepresentation;
}

MyJokerChange::~MyJokerChange() = default;


MyJokerChange::MyJokerChange(const MyPoint &positionChange, char jokerRepresentation) : positionChange(
        positionChange), jokerRepresentation(jokerRepresentation) {}

MyJokerChange::MyJokerChange(const MyPoint &positionChange, GamePiece::Type jokerRepresentation) : positionChange(
        positionChange), jokerRepresentation(nonjoker_lowercase_char_from_type(jokerRepresentation)) {}
