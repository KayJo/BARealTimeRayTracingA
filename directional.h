#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H
#include "light.h"

class Directional : public Light
{
public:
    Directional();
    Directional(float l, RGB col, QVector3D d);
    Directional(const Directional& dl);
    virtual ~Directional();

    virtual Light* clone() const;
    virtual QVector3D get_direction(ShadeRec &sr);
    virtual RGB L(ShadeRec &sr);
    virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;

    void set_radiance_factor(float l);
    void set_color(RGB col);
    void set_direction(QVector3D d);

private:
    float ls;
    RGB color;
    QVector3D dir;
};

inline void Directional::set_radiance_factor(float l){
    ls = l;
}

inline void Directional::set_color(RGB col){
    color = col;
}

inline void Directional::set_direction(QVector3D d){
    dir = d;
}

#endif // DIRECTIONAL_H
