#ifndef PERFECTTRANSMITTER_H
#define PERFECTTRANSMITTER_H

#include "btdf.h"

class PerfectTransmitter : public BTDF
{
public:
    PerfectTransmitter();
    PerfectTransmitter(const PerfectTransmitter& pt);
    virtual ~PerfectTransmitter();

    virtual PerfectTransmitter* clone() const;
    RGB f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const;
    RGB sample_f(const ShadeRec &sr, const QVector3D &wo, QVector3D &wt) const;
    RGB rho(const ShadeRec &sr, const QVector3D &wo) const;
    bool tir(const ShadeRec &sr) const;

    void set_kt(float _kt);
    void set_ior(float _ior);

private:
    float kt;
    float ior;
};

inline void PerfectTransmitter::set_kt(float _kt)
{
    kt = _kt;
}

inline void PerfectTransmitter::set_ior(float _ior)
{
    ior = _ior;
}

#endif // PERFECTTRANSMITTER_H
