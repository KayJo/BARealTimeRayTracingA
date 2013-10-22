#include "viewplane.h"
#include "regularsampler.h"

ViewPlane::ViewPlane() :
    hres(400),
    vres(400),
    s(1.0),
    sampler_ptr(new RegularSampler(1)),
    show_out_of_gammut(false),
    gamma(1.0),
    inv_gamma(1.0),
    max_depth(5)
{
}

ViewPlane::ViewPlane(const int hr, const int vr, const float ps, Sampler* s_ptr) :
    hres(hr),
    vres(vr),
    s(ps),
    sampler_ptr(s_ptr),
    show_out_of_gammut(false),
    gamma(1.0),
    inv_gamma(1.0),
    max_depth(5)
{
}

ViewPlane::ViewPlane(const ViewPlane &vp) :
    hres(vp.hres),
    vres(vp.vres),
    s(vp.s),
    num_samples(vp.num_samples),
    show_out_of_gammut(vp.show_out_of_gammut),
    gamma(vp.gamma),
    inv_gamma(vp.inv_gamma),
    max_depth(vp.max_depth)
{
    if(vp.sampler_ptr) {
        sampler_ptr = vp.sampler_ptr->clone();
    } else {
        sampler_ptr = NULL;
    }
}

ViewPlane::~ViewPlane()
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

}

void ViewPlane::set_sampler(Sampler *s_ptr)
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    num_samples = s_ptr->get_num_samples();
    sampler_ptr = s_ptr;
}

void ViewPlane::set_samples(const int ns)
{
    num_samples = ns;

    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    sampler_ptr = new RegularSampler(num_samples);
}
