#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"

class Sphere : public Geometry
{
public:
    Sphere();
    Sphere(const QVector3D ce, const double r);
    Sphere(const Sphere& sp);
    virtual ~Sphere();

    virtual Sphere* clone() const;
    void set_center(const float x, const float y, const float z);
    void set_center(const QVector3D& ce);
    void set_radius(const double r);
    bool hit(const Ray &ray, double &tmin, ShadeRec &sr) const;
    virtual bool shadowHit(const Ray &ray, float &tmin) const;

private:

    QVector3D center;       //Mittelpunkt des Sphere
    double radius;           //Radius des Sphere
    static const double kEpsilon;
};

inline void Sphere::set_center(const float x, const float y, const float z){
    center.setX(x);
    center.setY(y);
    center.setZ(z);
}

inline void Sphere::set_center(const QVector3D &ce){
    center.setX(ce.x());
    center.setY(ce.y());
    center.setZ(ce.z());
}

inline void Sphere::set_radius(const double r){
    radius = r;
}

#endif // SPHERE_H
