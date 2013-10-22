#include "regularsampler.h"
#include <cmath>

RegularSampler::RegularSampler()
{
}

RegularSampler::RegularSampler(int ns) :
    Sampler(ns)
{
    generate_samples();
}

RegularSampler::RegularSampler(const RegularSampler &r)
    :Sampler(r)
{
    generate_samples();
}

RegularSampler::~RegularSampler()
{
}

RegularSampler* RegularSampler::clone() const
{
    return new RegularSampler(*this);
}

void RegularSampler::generate_samples()
{
    int n = (int) sqrt((float)num_samples);

    for(int j = 0; j < num_sets; j++){
        for(int p = 0; p < n; p++){
            for(int q = 0;q < n; q++){
                samples.push_back(QPoint((q + 0.5) / n, (p + 0.5) / n));
            }
        }
    }
}
