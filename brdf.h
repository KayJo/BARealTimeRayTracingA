#ifndef BRDF_H
#define BRDF_H

#include <QVector3D>
#include "sampler.h"
#include "shaderec.h"
#include "rgb.h"
class BRDF
{
public:
    BRDF();
    BRDF(const BRDF& bf);
    virtual ~BRDF();
    virtual BRDF* clone() const = 0;
    virtual RGB f(const ShadeRec& sr, const QVector3D& wi, const QVector3D& wo) const = 0;
    virtual RGB sample_f(const ShadeRec& sr, QVector3D& wi, const QVector3D& wo) const = 0;
    virtual RGB rho(const ShadeRec& sr, const QVector3D& wo) const = 0;
    void set_sampler(Sampler* sp_ptr);

private:
    Sampler* sampler_ptr;
};

#endif // BRDF_H
