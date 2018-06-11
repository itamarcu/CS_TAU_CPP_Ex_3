#include "MyPoint.h"

int MyPoint::getX() const {
    return x;
}

int MyPoint::getY() const {
    return y;
}

MyPoint::MyPoint(int x, int y) : x(x), y(y) {}

MyPoint::MyPoint(int x, int y, bool start_from_one) : x(x + start_from_one), y(y + start_from_one) {}


MyPoint::~MyPoint() = default;