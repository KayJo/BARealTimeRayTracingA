#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include "rgb.h"
#include "shaderec.h"

class ShadeRec;
class Light
{
public:
    Light();
    Light(const Light& l);
    virtual ~Light();

    virtual Light* clone() const = 0;
    virtual QVector3D get_direction(ShadeRec& sr) = 0;
    virtual RGB L(ShadeRec& sr);
    virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const = 0;
    bool castsShadows();
    void setShadows(bool _shadows);

private:
    bool shadows;
};

inline void Light::setShadows(bool _shadows)
{
    shadows = _shadows;
}

#endif // LIGHT_H
