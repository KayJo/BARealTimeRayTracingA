#include "perfectspecular.h"
#include "constants.h"

PerfectSpecular::PerfectSpecular() :
    kr(0.0),
    cr(black)
{
}

PerfectSpecular::PerfectSpecular(const PerfectSpecular &ps) :
    BRDF(ps),
    kr(ps.kr),
    cr(ps.cr)
{
}

PerfectSpecular::~PerfectSpecular()
{
}

PerfectSpecular* PerfectSpecular::clone() const
{
    return new PerfectSpecular(*this);
}

//Gibt Schwarz zurück da die Funktion in dieser Klasse nicht genutzt wird
RGB PerfectSpecular::f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const
{
    return black;
}

//Zur Berechnung der Richtung des reflektierenden Strahls, sowie zur Berechnung der reflektierten
//Strahldichte
RGB PerfectSpecular::sample_f(const ShadeRec &sr, QVector3D &wi, const QVector3D &wo) const
{
    float nWo = QVector3D::dotProduct(sr.normal, wo);
    wi = -wo + 2.0 * sr.normal * nWo;

//    QColor c;
    float nWi = QVector3D::dotProduct(sr.normal, wi);
//    c.setRedF((cr.redF() * kr) / nWi);
//    c.setGreenF((cr.greenF() * kr) / nWi);
//    c.setBlueF((cr.blueF() * kr) / nWi);

    return ((cr * kr) / nWi);
}

//Gibt Schwarz zurück da die Funktion in dieser Klasse nicht genutzt wird
RGB PerfectSpecular::rho(const ShadeRec &sr, const QVector3D &wo) const
{
    return black;
}
