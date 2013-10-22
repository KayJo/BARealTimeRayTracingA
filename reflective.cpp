#include "reflective.h"
#include "constants.h"

Reflective::Reflective() :
    reflective_brdf(new PerfectSpecular)
{
}

Reflective::Reflective(const Reflective &rf) :
    Phong(rf)
{
    if(rf.reflective_brdf) {
        reflective_brdf = rf.reflective_brdf;
    } else {
        reflective_brdf = NULL;
    }
}

Reflective::~Reflective()
{
    if(reflective_brdf){
        delete reflective_brdf;
        reflective_brdf = NULL;
    }
}

Reflective* Reflective::clone() const
{
    return new Reflective(*this);
}

RGB Reflective::ray_cast_shade(ShadeRec &sr)
{
    return black;
}

RGB Reflective::whitted_shade(ShadeRec &sr)
{
    RGB L(Phong::whitted_shade(sr));

    QVector3D wo = -sr.ray.d;
    QVector3D wi;
    RGB fr = reflective_brdf->sample_f(sr,wi,wo);
    Ray reflected_ray(sr.hit_point, wi);

    //QColor trRay = sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
    float nWi = QVector3D::dotProduct(sr.normal, wi);
//    L.setRgbF(L.redF() + fr.redF() * trRay.redF() * nWi,
//              L.greenF() + fr.greenF() * trRay.greenF() * nWi,
//              L.blueF() + fr.blueF() * trRay.blueF() * nWi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * nWi;

    return L;
}
