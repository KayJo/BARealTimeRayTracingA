#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "light.h"

class PointLight : public Light
{
public:
    PointLight();
    PointLight(float l, RGB col, QVector3D loc);
    PointLight(const PointLight& pl);
    virtual ~PointLight();

    virtual Light* clone() const;
    virtual QVector3D get_direction(ShadeRec &sr);
    virtual RGB L(ShadeRec &sr);
    virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;

    void set_radiance_factor(float l);
    void set_color(RGB col);
    void set_location(QVector3D loc);

private:
    float ls;
    RGB color;
    QVector3D location;
};

inline void PointLight::set_radiance_factor(float l){
    ls = l;
}

inline void PointLight::set_color(RGB col){
    color = col;
}

inline void PointLight::set_location(QVector3D loc){
    location = loc;
}

#endif // POINTLIGHT_H
