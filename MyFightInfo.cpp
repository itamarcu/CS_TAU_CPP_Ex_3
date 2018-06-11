#include "MyFightInfo.h"

const Point &MyFightInfo::getPosition() const {
    return position;
}

char MyFightInfo::getPiece(int player) const {
    if (player == FIRST_PLAYER_CONST) {
        return firstPlayerPiece;
    } else if (player == SECOND_PLAYER_CONST) {
        return secondPlayerPiece;
    }
    return 0;
}

int MyFightInfo::getWinner() const {
    return winner;
}

MyFightInfo::~MyFightInfo() = default;

MyFightInfo::MyFightInfo(int winner, const Point &position, char firstPlayerPiece, char secondPlayerPiece) : winner(
        winner), position(position), firstPlayerPiece(firstPlayerPiece), secondPlayerPiece(secondPlayerPiece) {}
