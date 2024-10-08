#include "dPosition.h"

dPosition::dPosition(double x, double y) : x(x), y(y) {}

dPosition::dPosition(const dPosition& other)
{
    this->x = other.x;
    this->y = other.y;
}
