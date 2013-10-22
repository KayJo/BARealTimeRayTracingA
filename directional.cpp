#include "directional.h"
#include "constants.h"

Directional::Directional() :
    ls(1.0),
    color(white),
    dir(0,1,0)
{
}

Directional::Directional(float l, RGB col, QVector3D d) :
    ls(l),
    color(col),
    dir(d)
{
}

Directional::Directional(const Directional &dl) :
    Light(dl),
    ls(dl.ls),
    color(dl.color),
    dir(dl.dir)
{
}

Directional::~Directional()
{
}

Light* Directional::clone() const
{
    return new Directional(*this);
}

QVector3D Directional::get_direction(ShadeRec &sr)
{
    return dir;
}

RGB Directional::L(ShadeRec &sr)
{   
    return RGB(ls * color.r, ls * color.g, ls * color.b);
}

bool Directional::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    int numObjects = sr.w.objects.size();
    float d = dir.distanceToPoint(ray.o);

    for(int j = 0; j < numObjects; j++) {
        if(sr.w.objects[j]->shadowHit(ray, t) && t < d) {
            return true;
        }
    }

    return false;
}
