#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "phong.h"
#include "perfectspecular.h"

class Reflective : public Phong
{
public:
    Reflective();
    Reflective(const Reflective& rf);
    virtual ~Reflective();

    virtual Reflective* clone() const;
    virtual RGB ray_cast_shade(ShadeRec &sr);
    virtual RGB whitted_shade(ShadeRec &sr);

    void setKR(float _kr);
    void setCR(const RGB& _cr);

private:
    PerfectSpecular* reflective_brdf;
};





//Hier müssen noch genauer die Setter Funktionen definiert werden
inline void Reflective::setKR(float _kr) {
    reflective_brdf->set_kr(_kr);
}

inline void Reflective::setCR(const RGB &_cr) {
    reflective_brdf->set_cr(_cr);
}

#endif // REFLECTIVE_H
