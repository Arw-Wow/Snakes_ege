#include "Position.h"

Position::Position(int x, int y) : x(x), y(y) {}

Position::Position(const Position& other)
{
    this->x = other.x;
    this->y = other.y;
}
