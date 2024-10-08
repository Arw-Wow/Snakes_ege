#include "Size.h"

Size::Size(int w, int h) : w(w), h(h) {}

Size::Size(const Size& other)
{
    this->w = other.w;
    this->h = other.h;
}
