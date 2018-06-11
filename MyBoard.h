#ifndef CS_TAU_CPP_EX_2_MYBOARD_H
#define CS_TAU_CPP_EX_2_MYBOARD_H


#include <memory>
#include "Board.h"
#include "GamePiece.h"
#include "Auxiliary.h"

class MyBoard : public Board {


public:
    int getPlayer(const Point &pos) const override; // 1 for player 1's piece, 2 for 2, 0 if empty
    ~MyBoard() override;

    explicit MyBoard(const std::vector<std::vector<std::shared_ptr<GamePiece>>> &grid);

    MyBoard();


    std::vector<std::vector<std::shared_ptr<GamePiece >>> grid;
private:

    /**
     * initialize an empty grid
     */
    void initEmptyGrid() ;
};


#endif //CS_TAU_CPP_EX_2_MYBOARD_H
