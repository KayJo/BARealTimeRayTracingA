#include "plane.h"

const double Plane::kEpsilon = 0.001;

Plane::Plane() :
    normal(0,1,0),
    a(0.0,0.0,0.0)
{
}

Plane::Plane(const QVector3D& n, const QVector3D& aP) :
    normal(n),
    a(aP)
{
}

Plane::Plane(const Plane &plane) :
    Geometry(plane),
    normal(plane.normal),
    a(plane.a)
{
}

Plane::~Plane()
{
}

Plane* Plane::clone() const
{
    return new Plane(*this);
}

bool Plane::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    double t = QVector3D::dotProduct((a - ray.o), normal) / QVector3D::dotProduct(ray.d, normal);

    if(t > kEpsilon){
        tmin = t;
        sr.normal = normal;
        sr.local_hit_point = ray.o * t * ray.d;

        return true;
    } else {
        return false;
    }
}

bool Plane::shadowHit(const Ray &ray, float &tmin) const
{
    double t = QVector3D::dotProduct((a - ray.o), normal) / QVector3D::dotProduct(ray.d, normal);

    if(t > kEpsilon) {
        tmin = t;
        return true;
    } else {
        return false;
    }
}
