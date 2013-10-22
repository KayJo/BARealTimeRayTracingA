#include "material.h"
#include "constants.h"

Material::Material()
{
}

Material::Material(const Material &ma)
{
}

Material::~Material()
{
}

RGB Material::ray_cast_shade(ShadeRec &sr)
{
    return black;
}

RGB Material::whitted_shade(ShadeRec &sr)
{
    return black;
}
