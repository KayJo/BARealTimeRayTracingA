#include "rgb.h"

RGB::RGB() :
    r(0.0),
    g(0.0),
    b(0.0)
{
}

RGB::RGB(float _rgb) :
    r(_rgb),
    g(_rgb),
    b(_rgb)
{
}

RGB::RGB(float _r, float _g, float _b) :
    r(_r),
    g(_g),
    b(_b)
{
}

RGB::RGB(const RGB &rgb) :
    r(rgb.r),
    g(rgb.g),
    b(rgb.b)
{
}

RGB::~RGB()
{
}

RGB& RGB::operator =(const RGB& _rgb)
{
    if(this == &_rgb) {
        return (*this);
    }

    r = _rgb.r;
    g = _rgb.g;
    b = _rgb.b;

    return (*this);
}
