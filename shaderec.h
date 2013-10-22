#ifndef SHADEREC_H
#define SHADEREC_H

#include <QVector3D>
class Material;
//class World;
#include "world.h"
#include "ray.h"

class ShadeRec
{
public:

//    ShadeRec();

    ShadeRec(World& wr);

    ShadeRec(const ShadeRec& sr);

    virtual ~ShadeRec();

    bool hit_an_object;
    Material* material_ptr;
    QVector3D hit_point;
    QVector3D local_hit_point;
    QVector3D normal;
    Ray ray;
    int depth;
    double t;
    World& w;



};

#endif // SHADEREC_H
