#ifndef __JOKER_CHANGE_H_
#define __JOKER_CHANGE_H_

//--------------------------
// forward declaration
class Point;
//--------------------------

class JokerChange {
public:
	virtual const Point& getJokerChangePosition() const = 0;
	virtual char getJokerNewRep() const = 0; // R, P, S or B (but NOT J and NOT F)
	virtual ~JokerChange() {}
};

#endif