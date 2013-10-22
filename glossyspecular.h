#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H

#include "brdf.h"

class GlossySpecular : public BRDF
{
public:
    GlossySpecular();
    GlossySpecular(const GlossySpecular& gl);
    virtual ~GlossySpecular();

    virtual GlossySpecular* clone() const;
    RGB f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const;
    RGB sample_f(const ShadeRec &sr, QVector3D &wi, const QVector3D &wo) const;
    RGB rho(const ShadeRec &sr, const QVector3D &wo) const;

    void set_ks(float _ks);
    void set_cs(const RGB& _cs);
    void set_exponent(int _exp);


private:
    float ks;
    RGB cs;
    int exp;
};

inline void GlossySpecular::set_ks(float _ks)
{
    ks = _ks;
}

inline void GlossySpecular::set_cs(const RGB &_cs)
{
    cs = _cs;
}

inline void GlossySpecular::set_exponent(int _exp)
{
    exp = _exp;
}

#endif // GLOSSYSPECULAR_H
