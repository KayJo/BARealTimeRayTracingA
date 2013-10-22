#include "phong.h"
#include "world.h"
#include "light.h"
#include "constants.h"

Phong::Phong() :
    ambient_brdf(new Lambertian),
    diffuse_brdf(new Lambertian),
    specular_brdf(new GlossySpecular)
{
}

Phong::Phong(const Phong &ph) : Material(ph)
{
    if(ph.ambient_brdf) {
        ambient_brdf = ph.ambient_brdf->clone();

    } else {
        ambient_brdf = NULL;
    }

    if(ph.diffuse_brdf) {
        diffuse_brdf = ph.diffuse_brdf->clone();
    } else {
        diffuse_brdf = NULL;
    }

    if(ph.specular_brdf) {
        specular_brdf = ph.specular_brdf->clone();
    } else {
        specular_brdf = NULL;
    }
}

Phong::~Phong()
{
    if(ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = NULL;
    }

    if(diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }

    if(specular_brdf){
        delete specular_brdf;
        specular_brdf = NULL;
    }
}

Phong* Phong::clone() const
{
    return new Phong(*this);
}

RGB Phong::ray_cast_shade(ShadeRec &sr)
{
    return black;
}

RGB Phong::whitted_shade(ShadeRec &sr)
{
    QVector3D wo = -sr.ray.d;
    RGB L = ambient_brdf->rho(sr,wo) * sr.w.ambient_ptr->L(sr);
    int num_lights = sr.w.lights.size();

    for(int j = 0; j < num_lights; j++){
        QVector3D wi = sr.w.lights[j]->get_direction(sr);
        float nWi = QVector3D::dotProduct(sr.normal, wi);

        if(nWi > 0.0){
            bool inShadow = false;

            if(sr.w.lights[j]->castsShadows()) {
                Ray shadowRay(sr.hit_point, wi);
                inShadow = sr.w.lights[j]->inShadow(shadowRay, sr);

            }

            if(!inShadow) {
                L += (diffuse_brdf->f(sr,wo,wi) +
                      specular_brdf->f(sr,wo,wi)) *
                        sr.w.lights[j]->L(sr) *
                        nWi;

            }
        }

        return L;
    }
}
