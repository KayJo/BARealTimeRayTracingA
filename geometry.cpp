#include "geometry.h"

Geometry::Geometry() :
    material_ptr(NULL)
{
}

Geometry::Geometry(const Geometry &geo)
{
    if(geo.material_ptr) {
        material_ptr = geo.material_ptr->clone();
    } else {
        material_ptr = NULL;
    }
}

Geometry::~Geometry()
{
    if(material_ptr){
        delete material_ptr;
        material_ptr = NULL;
    }
}

void Geometry::set_material(Material *m_ptr)
{
    material_ptr = m_ptr;
}

Material* Geometry::get_material() const
{
    return material_ptr;
}
