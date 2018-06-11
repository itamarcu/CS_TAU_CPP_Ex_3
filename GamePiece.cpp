#include <iostream>
#include "GamePiece.h"
#include "Auxiliary.h"


char GamePiece::to_char() {
    char ch;
    if (isJoker)
        ch = JOKER_CHAR;
    else
        switch (type) {
            case Rock:
                ch = ROCK_CHAR;
                break;
            case Paper:
                ch = PAPER_CHAR;
                break;
            case Scissors:
                ch = SCISSORS_CHAR;
                break;
            case Bomb:
                ch = BOMB_CHAR;
                break;
            case None:
                ch = JOKER_CHAR;
                break; // Notice this
            case Flag:
                ch = FLAG_CHAR;
                break;
            default:;
                std::cerr << "Unknown type in store_game... cmon guys" << std::endl;
                ch = '@';
                break;
        }

    if (!player) // player 2
        ch = std::tolower(ch, std::locale()); // to lowercase

    return ch;
}

bool GamePiece::canMove() {
    switch (type) {
        case None:
            std::cerr << "BUG 16239817247" << std::endl;
            return false;
        case Rock:
        case Paper:
        case Scissors:
            return true;
        case Bomb:
        case Flag:
            return false;
        default:
            std::cerr << "BUG 7952234678123" << std::endl;
            break;
    }
    return false;
}

GamePiece::Type GamePiece::getType() const {
    return type;
}

GamePiece::Type type_from_char(const char c) {
    switch (c) {
        case ROCK_CHAR:
            return GamePiece::Type::Rock;
        case PAPER_CHAR:
            return GamePiece::Type::Paper;
        case SCISSORS_CHAR:
            return GamePiece::Type::Scissors;
        case BOMB_CHAR:
            return GamePiece::Type::Bomb;
        case JOKER_CHAR:
            return GamePiece::Type::None;
        case FLAG_CHAR:
            return GamePiece::Type::Flag;
        default:
            std::cout << "ERROR 95087216986345: char is " << c << std::endl;
            return GamePiece::Type::None;
    }
}


char nonjoker_lowercase_char_from_type(const GamePiece::Type gamePieceType) {
    char ch = GamePiece::chrFromType(gamePieceType);
    return ch;
}

char GamePiece::chrFromType(const Type &gamePieceType) {

    char ch;
    switch (gamePieceType) {
        case Rock:
            ch = ROCK_CHAR;
            break;
        case Paper:
            ch = PAPER_CHAR;
            break;
        case Scissors:
            ch = SCISSORS_CHAR;
            break;
        case Bomb:
            ch = BOMB_CHAR;
            break;
        case None:
            ch = JOKER_CHAR;
            break; // Notice
        case Flag:
            ch = FLAG_CHAR;
            break;
        default:;
            std::cerr << "Unknown type in char_from_type... c'mon guys" << std::endl;
            ch = '@';
            break;
    }
    return ch;
}
