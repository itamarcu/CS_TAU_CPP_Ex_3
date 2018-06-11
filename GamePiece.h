#ifndef CS_TAU_CPP_EX_2_GAMEPIECE_H
#define CS_TAU_CPP_EX_2_GAMEPIECE_H

/**
 * game piece type - for jokers, this is what their non-joker type is
*/


class GamePiece {
public:
    enum Type {
        None, // empty spaces are this type
        Rock, Paper, Scissors, Bomb,//Jokers have a current type but also the boolean
        Flag // jokers can't be flags
    };

    bool player;
    Type type;
    bool isJoker;

    /**
     * initialize game piece
     * @param playerIsFirst - true if it's the first false if it's the second
     * @param pieceType the type of piece (current "type", if it's a joker)
     * @param pieceIsJoker true if piece is a joker
     */
    explicit GamePiece(const bool playerIsFirst, const Type pieceType, const bool pieceIsJoker = false) :
            player(playerIsFirst), type(pieceType), isJoker(pieceIsJoker) {}

    /**
     *
     * @return char representing type and player. Jokers give J always.
     */
    char to_char();

    /**
     *
     * @return true if this unit can move (if it is not a flag or a bomb or a bomb-joker)
     */
    bool canMove();

    Type getType() const;

    static char chrFromType(const Type &gamePieceType);
};


GamePiece::Type type_from_char(const char c);

char nonjoker_lowercase_char_from_type(const GamePiece::Type gamePieceType);

#endif //CS_TAU_CPP_EX_2_GAMEPIECE_H
