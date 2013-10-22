#ifndef REGULARSAMPLER_H
#define REGULARSAMPLER_H
#include "sampler.h"

class RegularSampler : public Sampler
{
public:
    RegularSampler();
    RegularSampler(int ns);
    RegularSampler(const RegularSampler& r);
    virtual ~RegularSampler();

    virtual RegularSampler* clone() const;
    virtual void generate_samples();
};

#endif // REGULARSAMPLER_H
