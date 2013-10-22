#include "ambient.h"
#include "constants.h"

Ambient::Ambient() :
    ls(1.0),
    color(white)
{
}

Ambient::Ambient(float l, RGB col) :
    ls(l),
    color(col)
{
}

Ambient::Ambient(const Ambient &am) :
    Light(am),
    ls(am.ls),
    color(am.color)
{
}

Ambient::~Ambient()
{

}

Light* Ambient::clone() const
{
    return new Ambient(*this);
}

QVector3D Ambient::get_direction(ShadeRec &sr)
{
    return QVector3D(0.0,0.0,0.0);
}

RGB Ambient::L(ShadeRec &sr)
{
    return RGB(ls * color.r, ls * color.g, ls * color.b);
}

bool Ambient::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    return false;
}



