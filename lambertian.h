#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "brdf.h"

class Lambertian : public BRDF
{
public:
    Lambertian();
    Lambertian(const Lambertian& la);
    virtual ~Lambertian();

    virtual Lambertian* clone() const;

    RGB f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const;
    RGB sample_f(const ShadeRec &sr, QVector3D &wi, const QVector3D &wo) const;
    RGB rho(const ShadeRec &sr, const QVector3D &wo) const;

    void set_kd(float _kd);
    void set_cd(const RGB& _cd);

private:
    float kd;
    RGB cd;
};


inline void Lambertian::set_kd(float _kd){
    kd = _kd;
}

inline void Lambertian::set_cd(const RGB& _cd){
    cd = _cd;
}

#endif // LAMBERTIAN_H
