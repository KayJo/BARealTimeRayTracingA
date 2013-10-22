#include "raytracer.h"
#include "constants.h"
RayTracer::RayTracer() :
    world_ptr(NULL),
    restart(false),
    abort(false)
{
}

RayTracer::RayTracer(World *w_ptr) :
    world_ptr(w_ptr)
{
}

//RayTracer::RayTracer(World &w_ptr) :
//    world_ptr(w_ptr)
//{
//}

RayTracer::RayTracer(const RayTracer &rt)
{

//    if(rt.world_ptr) {
//        world_ptr = rt.world_ptr;
//    }
}

void RayTracer::run()
{
    QThread::run();
}

RayTracer::~RayTracer(){
    if(world_ptr){
        world_ptr = NULL;
    }
}

RayTracer* RayTracer::clone() const
{
    return new RayTracer(*this);
}

RGB RayTracer::trace_ray(const Ray &ray) const
{
    return black;
}

RGB RayTracer::trace_ray(const Ray ray, const int depth) const{
    return black;
}

void RayTracer::restartTracing() {
    restart = true;
}


