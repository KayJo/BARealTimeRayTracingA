#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <QVector3D>
#include "camera.h"
#include "material.h"
//#include "shaderec.h"

class ShadeRec;

class Geometry
{
public:
    Geometry();
    Geometry(const Geometry& geo);
    virtual ~Geometry();
    virtual Geometry* clone() const = 0;
    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
    virtual bool shadowHit(const Ray& ray, float& tmin) const = 0;

    void set_material(Material* m_ptr);
    Material* get_material() const;

private:
    Material* material_ptr;


};




#endif // GEOMETRY_H
