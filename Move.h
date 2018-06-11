#ifndef __MOVE_H_
#define __MOVE_H_

//--------------------------
// forward declaration
class Point;
//--------------------------

class Move {
public:
	virtual const Point& getFrom() const = 0;
	virtual const Point& getTo() const = 0;
	virtual ~Move() {}
};

#endif