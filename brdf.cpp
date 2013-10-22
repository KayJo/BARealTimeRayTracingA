#include "brdf.h"

BRDF::BRDF() :
    sampler_ptr(NULL)
{
}

BRDF::BRDF(const BRDF &bf)
{
    if(bf.sampler_ptr) {
        sampler_ptr = bf.sampler_ptr->clone();

    } else {
        sampler_ptr = NULL;
    }
}

BRDF::~BRDF()
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void BRDF::set_sampler(Sampler *sp_ptr)
{
    sampler_ptr = sp_ptr;
}




