#include "PlannedMove.h"
const MyPoint & PlannedMove::getOrigin() const {
    return origin;
}

const MyPoint & PlannedMove::getDestination() const {
    return destination;
}

bool PlannedMove::getHasJokerChanged() const {
    return has_joker_changed;
}

const MyPoint &PlannedMove::getJokerPosition() const {
    return joker_position;
}

GamePiece::Type PlannedMove::getNewJokerType() const {
    return new_joker_type;
}
