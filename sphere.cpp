#include "sphere.h"
#include <cmath>

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere() :
    center(0.0,0.0,0.0),
    radius(1.0)
{
}

Sphere::Sphere(QVector3D ce, double r) :
    center(ce),
    radius(r)
{
}

Sphere::Sphere(const Sphere &sp) :
    Geometry(sp),
    center(sp.center),
    radius(sp.radius)
{
}

Sphere::~Sphere()
{
}

Sphere* Sphere::clone() const
{
    return new Sphere(*this);
}

bool Sphere::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    double t;
    QVector3D temp = ray.o - center;
    double a = QVector3D::dotProduct(ray.d, ray.d);
    double b = 2.0 * QVector3D::dotProduct(temp, ray.d);
    double c = QVector3D::dotProduct(temp, temp) - radius * radius;
    double disc = b * b - 4.0 * a * c;

    if(disc < 0.0){
        return false;
    } else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;   //kleinere Wurzel

        if(t > kEpsilon){
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return true;
        }

        t = (-b + e) / denom;    //größere Wurzel

        if(t > kEpsilon){
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return true;
        }
    }

    return false;
}

bool Sphere::shadowHit(const Ray &ray, float &tmin) const
{
    double t;
    QVector3D temp = ray.o - center;
    double a = QVector3D::dotProduct(ray.d, ray.d);
    double b = 2.0 * QVector3D::dotProduct(temp, ray.d);
    double c = QVector3D::dotProduct(temp, temp) - radius * radius;
    double disc = b * b - 4.0 * a * c;

    if(disc < 0.0){
        return false;
    } else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;   //kleinere Wurzel

        if(t > kEpsilon){
            tmin = t;

            return true;
        }

        t = (-b + e) / denom;    //größere Wurzel

        if(t > kEpsilon){
            tmin = t;

            return true;
        }
    }

    return false;
}
