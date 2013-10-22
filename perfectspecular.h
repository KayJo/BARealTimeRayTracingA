#ifndef PERFECTSPECULAR_H
#define PERFECTSPECULAR_H

#include "brdf.h"

class PerfectSpecular : public BRDF
{
public:
    PerfectSpecular();
    PerfectSpecular(const PerfectSpecular& ps);
    virtual ~PerfectSpecular();

    virtual PerfectSpecular* clone() const;
    RGB f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const;
    RGB sample_f(const ShadeRec &sr, QVector3D &wi, const QVector3D &wo) const;
    RGB rho(const ShadeRec &sr, const QVector3D &wo) const;

    void set_kr(float _kr);
    void set_cr(const RGB& _cr);
private:
    float kr;
    RGB cr;

};

inline void PerfectSpecular::set_kr(float _kr)
{
    kr = _kr;
}

inline void PerfectSpecular::set_cr(const RGB& _cr)
{
    cr = _cr;
}

#endif // PERFECTSPECULAR_H
