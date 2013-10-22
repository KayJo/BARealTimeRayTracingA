#include "perfecttransmitter.h"
#include <QVector3D>
#include <cmath>
#include "constants.h"

PerfectTransmitter::PerfectTransmitter() :
    kt(0.0),
    ior(0.0)
{
}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter &pt) :
    BTDF(pt),
    kt(pt.kt),
    ior(pt.ior)
{
}

PerfectTransmitter::~PerfectTransmitter()
{
}

PerfectTransmitter* PerfectTransmitter::clone() const
{
    return new PerfectTransmitter(*this);
}

RGB PerfectTransmitter::f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const
{
    return black;
}

//errechnet die gesendete Strahl Richtung und übergibt sie in den Parameter wt,
//wird nur aufgerufen wenn keine total internal reflection vorhanden ist.
RGB PerfectTransmitter::sample_f(const ShadeRec &sr, const QVector3D &wo, QVector3D &wt) const
{
    QVector3D n(sr.normal);
    float cosThetai = QVector3D::dotProduct(n,wo);
    float eta = ior;

    if(cosThetai < 0.0){
        cosThetai = -cosThetai;
        n = -n;
        eta = 1.0 / eta;

    }

    float temp = 1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta);
    float cosTheta2 = sqrt(temp);
    wt = -wo / eta - (cosTheta2 - cosThetai / eta) * n;

//    QColor white = QColor(Qt::white);
//    double absNWt = fabs(QVector3D::dotProduct(sr.normal, wt));
//    white.setRgbF((kt / (eta * eta) * white.redF() / absNWt),
//                  (kt / (eta * eta) * white.greenF() / absNWt),
//                  (kt / (eta * eta) * white.blueF() / absNWt));
//    return white;

    return (kt / (eta * eta) * white / fabs(QVector3D::dotProduct(sr.normal, wt)));
}

RGB PerfectTransmitter::rho(const ShadeRec &sr, const QVector3D &wo) const
{
    return black;
}

//To Check for total internal reflection
bool PerfectTransmitter::tir(const ShadeRec &sr) const
{
    QVector3D wo(-sr.ray.d);
    float cosThetai = QVector3D::dotProduct(sr.normal,wo);
    float eta = ior;

    if(cosThetai < 0.0){
        eta = 1.0 / eta;
    }

    return (1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta) < 0.0);
}
