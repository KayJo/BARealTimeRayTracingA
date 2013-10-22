#include "transparent.h"
#include <cmath>
#include "constants.h"

Transparent::Transparent() :
    reflective_brdf(new PerfectSpecular),
    specular_btdf(new PerfectTransmitter)
{
}

Transparent::Transparent(const Transparent &tr) :
    Phong(tr)
{
    if(tr.reflective_brdf) {
        reflective_brdf = tr.reflective_brdf->clone();
    } else {
        reflective_brdf = NULL;
    }

    if(tr.specular_btdf) {
        specular_btdf = tr.specular_btdf->clone();
    } else {
        specular_btdf = NULL;
    }
}

Transparent::~Transparent()
{
    if(reflective_brdf){
        delete reflective_brdf;
        reflective_brdf = NULL;
    }

    if(specular_btdf){
        delete specular_btdf;
        specular_btdf = NULL;
    }
}

Transparent* Transparent::clone() const
{
    return new Transparent(*this);
}

RGB Transparent::ray_cast_shade(ShadeRec &sr)
{
    return black;
}

RGB Transparent::whitted_shade(ShadeRec &sr)
{
    RGB L(Phong::whitted_shade(sr));

    QVector3D wo = -sr.ray.d;
    QVector3D wi;
    RGB fr = reflective_brdf->sample_f(sr,wi,wo);    //errechnet wi
    Ray reflected_ray(sr.hit_point, wi);

    if(specular_btdf->tir(sr)){

        L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
    } else {
        QVector3D wt;
        RGB ft = specular_btdf->sample_f(sr,wo,wt);  //errechet wt
        Ray transmitted_ray(sr.hit_point,wt);

        L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)
                * fabs(QVector3D::dotProduct(sr.normal, wi));
        L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1)
                * fabs(QVector3D::dotProduct(sr.normal, wt));

    }

    return L;
}
