#ifndef CS_TAU_CPP_EX_2_PLANNEDMOVER_H
#define CS_TAU_CPP_EX_2_PLANNEDMOVER_H

#include "GamePiece.h"
#include "Point.h"
#include "MyPoint.h"

/**
 *
 */
class PlannedMove {
    // Fields
private:
    bool is_good_format;
    MyPoint origin;
    MyPoint destination;
    bool has_joker_changed;
    MyPoint joker_position;
    GamePiece::Type new_joker_type;

    //Constructors
public:
    //For invalid moves:
    explicit PlannedMove(bool format) : is_good_format(format), origin(0, 0),
                                        destination(0, 0), has_joker_changed(false),
                                        joker_position(0, 0), new_joker_type(GamePiece::Type::None) {}

    //For non-joker moves:
    explicit PlannedMove(int x1, int y1, int x2, int y2)
            : is_good_format(true), origin(x1, y1),
              destination(x2, y2), has_joker_changed(false),
              joker_position(0, 0), new_joker_type(GamePiece::Type::None) {}

    //For joker moves:
    explicit PlannedMove(int x1, int y1, int x2, int y2,
                         int jx, int jy, GamePiece::Type jtype)
            : is_good_format(true), origin(x1, y1),
              destination(x2, y2), has_joker_changed(true),
              joker_position(jx, jy), new_joker_type(jtype) {}

    //GETTERS
public:
    const MyPoint & getOrigin() const;

    const MyPoint & getDestination() const;

    bool getHasJokerChanged() const;

    const MyPoint &getJokerPosition() const;

    GamePiece::Type getNewJokerType() const;
};



#endif //CS_TAU_CPP_EX_2_PLANNEDMOVER_H
