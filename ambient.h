#ifndef AMBIENT_H
#define AMBIENT_H
#include "light.h"

class Ambient : public Light
{
public:
    Ambient();
    Ambient(float l, RGB col);
    Ambient(const Ambient& am);
    virtual ~Ambient();
    virtual Light* clone() const;
    virtual QVector3D get_direction(ShadeRec &sr);
    virtual RGB L(ShadeRec &sr);
    virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;

    void set_radiance_factor(float l);
    void set_color(RGB col);

private:
    float ls;
    RGB color;
};

inline void Ambient::set_radiance_factor(float l){
    ls = l;
}

inline void Ambient::set_color(RGB col){
    color = col;
//    color.setRgba(col.rgba());
}

#endif // AMBIENT_H
