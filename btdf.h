#ifndef BTDF_H
#define BTDF_H
#include "rgb.h"
#include "shaderec.h"

class BTDF
{
public:
    BTDF();
    BTDF(const BTDF& bf);
    virtual ~BTDF();
    virtual BTDF* clone() const = 0;

    virtual RGB f(const ShadeRec& sr, const QVector3D& wi, const QVector3D& wo) const = 0;
    virtual RGB sample_f(const ShadeRec& sr, const QVector3D& wo, QVector3D& wt) const = 0;
    virtual RGB rho(const ShadeRec& sr, const QVector3D& wo) const = 0;
    virtual bool tir(const ShadeRec& sr)const = 0;
};

#endif // BTDF_H
