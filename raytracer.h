#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "rgb.h"
#include "ray.h"

class World;

class RayTracer : public QThread
{
    Q_OBJECT
public:
//    QMutex mutex;

    RayTracer();
    RayTracer(World* w_ptr);
    RayTracer(const RayTracer& rt);

    virtual void run();
    virtual ~RayTracer();

    virtual RayTracer* clone() const;
    virtual RGB trace_ray(const Ray& ray) const;
    virtual RGB trace_ray(const Ray ray, const int depth) const;
    virtual void restartTracing();


protected:
    World* world_ptr;
    bool restart;
    bool abort;
    QWaitCondition eventFinished;
    QMutex mutex;

};

#endif // RAYTRACER_H
