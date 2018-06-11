#ifndef CS_TAU_CPP_EX_2_MYPOINT_H
#define CS_TAU_CPP_EX_2_MYPOINT_H


#include "Point.h"

/**
 * This class implements Point interface
 */
class MyPoint : public Point {
public:
    int x;
    int y;

    MyPoint(int x, int y);

    MyPoint(int x, int y, bool start_from_one);

    ~MyPoint() override;

    explicit MyPoint(const Point &p) : x(p.getX()), y(p.getY()) {}

    int getX() const override;

    int getY() const override;


};


#endif //CS_TAU_CPP_EX_2_MYPOINT_H
