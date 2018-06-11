#ifndef CS_TAU_CPP_EX_2_MYMOVE_H
#define CS_TAU_CPP_EX_2_MYMOVE_H


#include "Move.h"
#include "MyPoint.h"

class MyMove : public Move {
public:
    MyMove(const MyPoint &from, const MyPoint &to);

    const Point &getFrom() const override;

    const Point &getTo() const override;

    ~MyMove() override;
private:
    MyPoint from;
    MyPoint to;
};


#endif //CS_TAU_CPP_EX_2_MYMOVE_H
