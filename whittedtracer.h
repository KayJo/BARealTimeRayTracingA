#ifndef WHITTEDTRACER_H
#define WHITTEDTRACER_H

#include "raytracer.h"

class WhittedTracer : public RayTracer
{
    Q_OBJECT
public:
    WhittedTracer();
    WhittedTracer(World* w_ptr);
//    WhittedTracer(const WhittedTracer& wt);

    virtual void run();
    virtual ~WhittedTracer();

    virtual WhittedTracer* clone() const;
    virtual RGB trace_ray(const Ray ray, const int depth) const;
    virtual void restartTracing();
};

#endif // WHITTEDTRACER_H
