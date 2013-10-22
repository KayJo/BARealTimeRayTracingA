#ifndef VIEWPLANE_H
#define VIEWPLANE_H
#include "sampler.h"

class ViewPlane
{
public:
    int hres;
    int vres;
    float s;
    int num_samples;
    Sampler* sampler_ptr;
    bool show_out_of_gammut;
    float gamma;
    float inv_gamma;
    int max_depth;

    ViewPlane();
    ViewPlane(const int hr, const int vr, const float ps, Sampler* s_ptr);
    ViewPlane(const ViewPlane& vp);
    virtual ~ViewPlane();

    void set_horizontal_resolution(const int hr);
    void set_vertical_resolution(const int vr);
    void set_pixel_size(const float ps);
    void set_sampler(Sampler* s_ptr);
    void set_samples(const int ns);
    void set_show_out_of_gammut(const bool sg);
    void set_gamma(const float g);
    void set_inv_gamma(const float inv_g);
    void set_max_depth(const int depth);



};

inline void ViewPlane::set_horizontal_resolution(const int hr){
    hres = hr;
}

inline void ViewPlane::set_vertical_resolution(const int vr){
    vres = vr;
}

inline void ViewPlane::set_pixel_size(const float ps){
    s = ps;
}

inline void ViewPlane::set_show_out_of_gammut(const bool sg){
    show_out_of_gammut = sg;
}

inline void ViewPlane::set_gamma(const float g){
    gamma = g;
}

inline void ViewPlane::set_inv_gamma(const float inv_g){
    inv_gamma = inv_g;
}

inline void ViewPlane::set_max_depth(const int depth){
    max_depth = depth;
}



#endif // VIEWPLANE_H
