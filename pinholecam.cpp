#include "pinholecam.h"
#include "viewplane.h"
#include "ray.h"
#include "world.h"
#include "sampler.h"
#include "constants.h"


PinholeCam::PinholeCam() :
    d(500),
    zoom(1.0)
{
}

PinholeCam::PinholeCam(const float distance, const float z) :
    d(distance),
    zoom(z)
{
}

PinholeCam::PinholeCam(const PinholeCam &pc) :
    Camera(pc),
    d(pc.d),
    zoom(pc.zoom)
{
}

PinholeCam::~PinholeCam()
{
}

Camera* PinholeCam::clone() const
{
    return new PinholeCam(*this);
}

//void PinholeCam::render_scene(World &w)
//{
//    RGB L;
//    ViewPlane vp(w.vp);
//    Ray ray;
//    int depth = 0;  //rekursions tiefe
//    QPoint sp;      //Abtastpunkt in [0,1] x [0,1]
//    QPoint pp;      //Abtastpunkt an einem Pixel

////    w.open_window(vp.hres, vp.vres);
////    w.open_window(vp.hres, vp.vres);
//    //hier einfach eine if zoomable abfrage starten
//    vp.s /= zoom;
//    ray.o = eye;

//    for(int r = 0; r < vp.vres; r++){   //vertikal, up
//        for(int c = 0; c < vp.hres; c++){   //horizontal, across
//            L = black;

//            for(int j = 0; j < vp.num_samples; j++){
//                sp = vp.sampler_ptr->sample_unit_square();
//                pp.setX(vp.s * (c - 0.5 * vp.hres + sp.x()));
//                pp.setY(vp.s * (r - 0.5 * vp.vres + sp.y()));
//                ray.d = ray_direction(pp);
////                w.tracer_ptr->mutex.lock();
//                L += w.tracer_ptr->trace_ray(ray,depth);
////                w.tracer_ptr->mutex.unlock();
//            }


//            L /= vp.num_samples;
//            L *= exposure_time;
//            w.display_pixel(r,c,L);
//        }

//    }
//}

QVector3D PinholeCam::ray_direction(const QPoint &p)
{
    QVector3D dir = (float)p.x() * u + (float)p.y() * v - d * w;
    dir.normalize();
    return dir;
}

void PinholeCam::zoomIn()
{
    d = d + 30;
}

void PinholeCam::zoomOut()
{
    d = d - 30;
}

bool PinholeCam::isZoomable()
{
    return true;
}

float PinholeCam::getZoomFactor()
{
    return zoom;
}
