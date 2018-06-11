#include "MyMove.h"

/**
 * get move starting point
 * @return Point subclass instance for starting point representation
 */
const Point &MyMove::getFrom() const {
    return from;
}
/**
 * get move destination
 * @return Point subclass instance for destination representation
 */
const Point &MyMove::getTo() const {
    return to;
}

MyMove::~MyMove()  = default;

MyMove::MyMove(const MyPoint &from, const MyPoint &to) : from(from), to(to) {}
