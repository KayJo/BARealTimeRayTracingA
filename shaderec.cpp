#include "shaderec.h"

//ShadeRec::ShadeRec()
//    :hit_an_object(false),
//      material_ptr(NULL),
//      depth(0),
//      w(NULL)
//{

//}

ShadeRec::ShadeRec(World& wr) :
    hit_an_object(false),
    material_ptr(NULL),
    depth(0),
    w(wr)
{
}

ShadeRec::ShadeRec(const ShadeRec &sr) :
      hit_an_object(sr.hit_an_object),
      material_ptr(sr.material_ptr),
      hit_point(sr.hit_point),
      local_hit_point(sr.local_hit_point),
      normal(sr.normal),
      ray(sr.ray),
      depth(sr.depth),
      w(sr.w)
{
}

ShadeRec::~ShadeRec()
{
}
