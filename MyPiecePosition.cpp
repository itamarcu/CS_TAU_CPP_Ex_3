#include "MyPiecePosition.h"

const Point &MyPiecePosition::getPosition() const {
    return position;
}

char MyPiecePosition::getPiece() const {
    return piece;
}

char MyPiecePosition::getJokerRep() const {
    return jokerRep;
}

MyPiecePosition::~MyPiecePosition() = default;

MyPiecePosition::MyPiecePosition(char piece, char jokerRep, const MyPoint &position) : piece(piece), jokerRep(jokerRep),
                                                                                       position(position) {}
