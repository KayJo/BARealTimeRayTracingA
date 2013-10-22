#include "whittedtracer.h"
#include "shaderec.h"
#include "world.h"
#include "constants.h"


WhittedTracer::WhittedTracer()
{
}

WhittedTracer::WhittedTracer(World *w_ptr) :
    RayTracer(w_ptr)
{
}

//WhittedTracer::WhittedTracer(const WhittedTracer &wt) :
//    RayTracer(wt)
//{
//}

void WhittedTracer::run()
{
//    RayTracer::run();
    forever{
        mutex.lock();

        RGB L;
        ViewPlane vp(world_ptr->vp);
        Ray ray;
        int depth = 0;  //rekursions tiefe
        QPoint sp;      //Abtastpunkt in [0,1] x [0,1]
        QPoint pp;      //Abtastpunkt an einem Pixel

    //    w.open_window(vp.hres, vp.vres);
    //    w.open_window(vp.hres, vp.vres);
        //hier einfach eine if zoomable abfrage starten
        if(world_ptr->camera_ptr->isZoomable()) {
            vp.s /= world_ptr->camera_ptr->getZoomFactor();
        }

        ray.o = world_ptr->camera_ptr->getEye();
        mutex.unlock();
        for(int r = 0; r < vp.vres; r++){       //vertikal, up
            if(restart) {
                break;
            }
            if(abort) {
                return;
            }
            for(int c = 0; c < vp.hres; c++){   //horizontal, across
                L = black;

                if(restart) {
                    break;
                }
                if(abort) {
                    return;
                }

                for(int j = 0; j < vp.num_samples; j++){
                    mutex.lock();
                    sp = vp.sampler_ptr->sample_unit_square();
                    pp.setX(vp.s * (c - 0.5 * vp.hres + sp.x()));
                    pp.setY(vp.s * (r - 0.5 * vp.vres + sp.y()));
                    ray.d = world_ptr->camera_ptr->ray_direction(pp);
                    L += trace_ray(ray,depth);
                    mutex.unlock();
                }

                mutex.lock();
                L /= vp.num_samples;
                L *= world_ptr->camera_ptr->getExposureTime();

                //Hier wird die signal funktion emitted
                //Es werden diese daten hier an die Welt gesendet
                world_ptr->display_pixel(r,c,L);
                mutex.unlock();
            }

        }
        mutex.lock();
        if(!restart) {
            eventFinished.wait(&mutex);
        }
        restart = false;
        mutex.unlock();

    }

}

WhittedTracer::~WhittedTracer()
{
    mutex.lock();
    abort = true;
    eventFinished.wakeOne();
    mutex.unlock();
    wait();
}

WhittedTracer* WhittedTracer::clone() const
{
    return new WhittedTracer(*this);
}

RGB WhittedTracer::trace_ray(const Ray ray, const int depth) const
{
    if(depth > world_ptr->vp.max_depth){
        return black;
    } else {
        ShadeRec sr(world_ptr->hit_objects(ray));

        if(sr.hit_an_object){
            sr.depth = depth;
            sr.ray = ray;

            return sr.material_ptr->whitted_shade(sr);
        } else {
            return world_ptr->background_color;
        }
    }
}

void WhittedTracer::restartTracing()
{
    if(!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        eventFinished.wakeOne();
    }
}
