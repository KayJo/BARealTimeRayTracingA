#include "lambertian.h"
#include "constants.h"

Lambertian::Lambertian() :
    kd(0.0)
{
}

Lambertian::Lambertian(const Lambertian &la) :
    BRDF(la),
    kd(la.kd),
    cd(la.cd)
{
}

Lambertian::~Lambertian()
{
}

Lambertian* Lambertian::clone() const
{
    return new Lambertian(*this);
}

RGB Lambertian::f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const
{
    //return F(cd.r * kd * INV_PI, cd.g * kd * INV_PI, cd.b * kd * INV_PI);
    return (cd * (kd * INV_PI));
}

RGB Lambertian::sample_f(const ShadeRec &sr, QVector3D &wi, const QVector3D &wo) const
{
    //wird nur im Path Tracer aufgerufen !!
    return black;
}

RGB Lambertian::rho(const ShadeRec &sr, const QVector3D &wo) const
{
//    QColor R;
//    R.setRedF(cd.redF() * kd);
//    R.setGreenF(cd.greenF() * kd);
//    R.setBlueF(cd.blueF() * kd);
    return (cd * kd);
}
