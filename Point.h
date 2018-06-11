#ifndef __POINT_H_
#define __POINT_H_

class Point {
public:
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual ~Point() = default;
};

#endif