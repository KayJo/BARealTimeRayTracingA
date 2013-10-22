#include "light.h"
#include "constants.h"


Light::Light() :
    shadows(true)
{
}

Light::Light(const Light &l) :
    shadows(l.shadows)
{
}

Light::~Light()
{
}

RGB Light::L(ShadeRec &sr)
{
    return black;
}

bool Light::castsShadows() {
    return shadows;
}
