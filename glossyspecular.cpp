#include "glossyspecular.h"
#include "constants.h"
#include <cmath>

GlossySpecular::GlossySpecular() :
    ks(0.0),
    cs(1.0),
    exp(0)
{
}

GlossySpecular::GlossySpecular(const GlossySpecular &gl) :
    BRDF(gl),
    ks(gl.ks),
    cs(gl.cs),
    exp(gl.exp)
{
}

GlossySpecular::~GlossySpecular()
{
}

GlossySpecular* GlossySpecular::clone() const
{
    return new GlossySpecular(*this);
}


//Gibt die eingespannte Version der Gleichung L(p,wo)=ks(r*wo)hoch e * ls*cl*(n*l)
//modeling specular highlights
RGB GlossySpecular::f(const ShadeRec &sr, const QVector3D &wi, const QVector3D &wo) const
{
    RGB L;
    float nWi = QVector3D::dotProduct(sr.normal, wi);
    //reflektierte Richtung r
    QVector3D r = -wi + 2.0 * sr.normal * nWi;
    float rWo = QVector3D::dotProduct(r, wo);

    if(rWo > 0.0){
//        float rgb = ;
        //Hier aufpassen!! Nicht sicher ob OperatorOverloading intern passiert!!!
        L = ks * pow(rWo, exp);
    }

    return L;
}

//wird genutzt für Glossy Reflection
RGB GlossySpecular::sample_f(const ShadeRec &sr, QVector3D &wi, const QVector3D &wo) const
{
    return black;
}

RGB GlossySpecular::rho(const ShadeRec &sr, const QVector3D &wo) const{
    return black;
}
