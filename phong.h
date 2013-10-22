#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "lambertian.h"
#include "glossyspecular.h"

class Phong : public Material
{
public:
    Phong();
    Phong(const Phong& ph);
    virtual ~Phong();

    virtual Phong* clone() const;
    virtual RGB ray_cast_shade(ShadeRec &sr);
    virtual RGB whitted_shade(ShadeRec &sr);

    //kr, cr, kd, cd, exp, ks, cs
//    void set_kr(float _kr);
//    void set_cr(RGB _cr);
    void set_kd(float _kd);
    void set_cd(RGB _cd);
    void set_exp(int _exp);
    void set_ks(float _ks);
    void set_cs(RGB _cs);

private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
    GlossySpecular* specular_brdf;
};

//inline void Phong::set_kr(float _kr)
//{
//    specular_brdf->set_kr(_kr);
//}

//inline void Phong::set_cr(RGB _cr)
//{
//    specular_brdf->set_cr(_cr);
//}

inline void Phong::set_kd(float _kd)
{
    ambient_brdf->set_kd(_kd);
    diffuse_brdf->set_kd(_kd);
}

inline void Phong::set_cd(RGB _cd)
{
    ambient_brdf->set_cd(_cd);
    diffuse_brdf->set_cd(_cd);
}

inline void Phong::set_ks(float _ks)
{
    specular_brdf->set_ks(_ks);
}

inline void Phong::set_cs(RGB _cs)
{
    specular_brdf->set_cs(_cs);
}

inline void Phong::set_exp(int _exp)
{
    specular_brdf->set_exponent(_exp);
}




#endif // PHONG_H
