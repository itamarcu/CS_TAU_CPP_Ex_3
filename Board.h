#ifndef __BOARD_H_
#define __BOARD_H_

//--------------------------
// forward declaration
class Point;
//--------------------------

class Board {
public:
	virtual int getPlayer(const Point& pos) const = 0; // 1 for player 1's piece, 2 for 2, 0 if empty
	virtual ~Board() = default;
};

#endif