#ifndef PLANE_H
#define PLANE_H
#include "geometry.h"

class Plane : public Geometry
{
public:
    Plane();
    Plane(const QVector3D& n, const QVector3D& aP);
    Plane(const Plane& plane);
    virtual ~Plane();

    virtual Plane* clone() const;
    void set_normal(const QVector3D& n);
    void set_a(const float x, const float y, const float z);
    void set_a(const QVector3D& aP);
    virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr) const;
    virtual bool shadowHit(const Ray &ray, float &tmin) const;
private:
    QVector3D normal;
    QVector3D a;
    static const double kEpsilon;

};


inline void Plane::set_normal(const QVector3D& n){
    normal.setX(n.x());
    normal.setY(n.y());
    normal.setZ(n.z());
}

inline void Plane::set_a(const float x, const float y, const float z){
    a.setX(x);
    a.setY(y);
    a.setZ(z);
}

inline void Plane::set_a(const QVector3D &aP){
    a.setX(aP.x());
    a.setY(aP.y());
    a.setZ(aP.z());
}



#endif // PLANE_H
