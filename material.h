#ifndef MATERIAL_H
#define MATERIAL_H
#include "shaderec.h"
#include "rgb.h"

class ShadeRec;

class Material
{
public:
    Material();
    Material(const Material& ma);
    virtual ~Material();

    virtual Material* clone() const = 0;
    virtual RGB ray_cast_shade(ShadeRec& sr);
    virtual RGB whitted_shade(ShadeRec& sr);

};

#endif // MATERIAL_H
