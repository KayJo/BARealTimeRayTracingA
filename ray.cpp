#include "ray.h"

Ray::Ray() :
    o(0.0,0.0,0.0),
    d(0.0,0.0,1.0)
{
}

Ray::Ray(const QVector3D origin, const QVector3D direction) :
    o(origin),
    d(direction)
{
}

Ray::Ray(const Ray &ray) :
    o(ray.o),
    d(ray.d)
{
}

Ray::~Ray()
{
}
