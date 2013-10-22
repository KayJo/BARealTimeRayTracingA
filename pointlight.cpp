#include "pointlight.h"
#include "constants.h"

PointLight::PointLight() :
    ls(1.0),
    color(Qt::white),
    location(0,1,1)
{
}

PointLight::PointLight(float l, RGB col, QVector3D loc) :
    ls(l),
    color(col),
    location(loc)
{
}

PointLight::PointLight(const PointLight &pl) :
    Light(pl),
    ls(pl.ls),
    color(pl.color),
    location(pl.location)
{
}

PointLight::~PointLight()
{
}

Light* PointLight::clone() const
{
    return new PointLight(*this);
}

QVector3D PointLight::get_direction(ShadeRec &sr)
{
    return (location - sr.hit_point).normalized();
}

RGB PointLight::L(ShadeRec &sr)
{
    return color * ls;
}

bool PointLight::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    int numObjects = sr.w.objects.size();
    float d = location.distanceToPoint(ray.o);

    for(int j = 0; j < numObjects; j++) {
        if(sr.w.objects[j]->shadowHit(ray, t) && t < d) {
            return true;
        }
    }

    return false;

}


