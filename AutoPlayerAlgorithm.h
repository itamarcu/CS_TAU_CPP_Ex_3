#ifndef CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H
#define CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H


#include "PlayerAlgorithm.h"
#include "PlannedMove.h"
#include "MyBoard.h"

class AutoPlayerAlgorithm : public PlayerAlgorithm {
private:
    unsigned int player; // 1 or 2
    unsigned int enemyPieceWhichJustAttacked;
    unsigned int ourPieceWhichJustAttacked;
    //2d board of ints representing knowledge on board, see enum
    unsigned int myBoard[N][M];

    /**
     * board cases, don't use directly! so you can use or operator and save as int
     */
    enum BoardCases {
        NoPlayer = 1, // start from 1
        OurPlayer = 2,
        EnemyPlayer = 1024,

        /**
         * could be with suspected on, when you think that a piece is some of the follows(we've seen it win in a fight) but might be a joker
         */
                Rock = 8,
        Scissors = 16,
        Paper = 32,

        /**
         * if we've seen a piece change its type it must be a joker, not suspected
         */
                Joker = 64,

        /**
         * will be used only on our pieces (because no way of knowing about enemy's)
         */
                Bomb = 128,

        Flag = 256,

//        /**
//         * to use when you don't know for sure it's a piece or joker
//         */
//                Suspected = 512,

        /**
         * false CanMove just means it hasn't moved yet, for enemy pieces (we can't really know)
         */
                CanMove = 4
    };

    /**
     * From MyBoard, returns a filtered vector of positions. A position will only
     * be returned if the piece on it is filtered in and not filtered out. For example,
     * if filter_in is `OurPlayer` and filter_out is `Movable` this will return
     * all pieces that belong to us and are not movable. You can also do stuff like
     * filter_in = `Joker | SecondPlayer` to get only jokers of enemy player.
     * @return only pieces that are "all of filter_in and none of filter_out"
     */
    unique_ptr<std::vector<MyPoint>> get_by_filter(unsigned int filter_in, unsigned int filter_out = 0) const;

    /**
     * new representation for joker
     * @param jokerPoint the joker point to change
     * @return new repr
     */
    char select_new_joker_repr(const MyPoint &jokerPoint);

    /**
     * add non joker pieces to initial board
     * @param vectorToFill vector of piece
     * @param availableSpots available spots to add in
     * @param count count of the piece
     * @param chr the chr of the piece
     * @param movable is it movable
     */
    void select_non_joker_piece_to_add(std::vector<unique_ptr<PiecePosition>> &vectorToFill,
                                       std::vector<MyPoint> &availableSpots, int count, char chr, bool movable);

    unique_ptr<JokerChange> select_joker_change(const unique_ptr<std::vector<MyPoint>> &jokerPositions, int pos);

    unsigned int encode_type_from_char(char c) const;

    /**
     * Creates and returns this movement to make, and updates knowledge
     */
    unique_ptr<Move> make_move(const MyPoint &from, const MyPoint &to);

public:

    explicit AutoPlayerAlgorithm(int player);

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) override;

    /**
     * notify on initial board
     * @param b the board to notify on
     * @param fights fights that were held on board
     */
    void notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) override;

    /**
     * notify function on opponent move, assumes no error in move
     * @param move the move of the opponent
     */
    void notifyOnOpponentMove(const Move &move) override;

    /**
     * notify fight result
     * @param fightInfo fight info
     */
    void notifyFightResult(const FightInfo &fightInfo) override;

    /**
     * get next move
     * @return next move
     */
    unique_ptr<Move> getMove() override;

    /**
     * get joker change
     * @return joker change, nullptr if no change;
     */
    unique_ptr<JokerChange> getJokerChange() override;

    ~AutoPlayerAlgorithm() override;

};


#endif //CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H
