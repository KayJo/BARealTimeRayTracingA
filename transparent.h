#ifndef TRANSPARENT_H
#define TRANSPARENT_H

#include "phong.h"
#include "perfecttransmitter.h"
#include "perfectspecular.h"


class Transparent : public Phong
{
public:
    Transparent();
    Transparent(const Transparent& tr);
    virtual ~Transparent();

    virtual Transparent* clone() const;
    virtual RGB ray_cast_shade(ShadeRec &sr);
    virtual RGB whitted_shade(ShadeRec &sr);

    void setKR(float _kr);
    void setCR(float _cr);
    void setKT(float _kt);
    void setIOR(float _ior);

private:

    PerfectSpecular* reflective_brdf;
    PerfectTransmitter* specular_btdf;
};


inline void Transparent::setKR(float _kr) {
    reflective_brdf->set_kr(_kr);
}

inline void Transparent::setCR(float _cr) {
    reflective_brdf->set_cr(_cr);
}

inline void Transparent::setKT(float _kt) {
    specular_btdf->set_kt(_kt);
}

inline void Transparent::setIOR(float _ior) {
    specular_btdf->set_ior(_ior);
}

//Hier müssen noch genauer die Setter Funktionen definiert werden

#endif // TRANSPARENT_H
