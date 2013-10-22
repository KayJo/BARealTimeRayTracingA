#include "sampler.h"
#include <algorithm>

Sampler::Sampler() :
    num_samples(1),
    num_sets(83),
    count(0),
    jump(0)
{
    setup_shuffled_indices();
}

Sampler::Sampler(int ns) :
    num_samples(ns),
    num_sets(83),
    count(0),
    jump(0)
{
    setup_shuffled_indices();
}

Sampler::Sampler(int ns, int sets) :
    num_samples(ns),
    num_sets(sets),
    count(0),
    jump(0)
{
    setup_shuffled_indices();
}

Sampler::Sampler(const Sampler &spl) :
    num_samples(spl.num_samples),
    num_sets(spl.num_sets),
    samples(spl.samples),
    shuffled_indices(spl.shuffled_indices),
    count(spl.count),
    jump(spl.jump)
{
}

Sampler::~Sampler()
{
}

//Um gewissen Faser im Bild vorzubeugen müssen die samples zufällig
//generiert werden, in dieser funktion werden die sample indices gemischt
void Sampler::setup_shuffled_indices()
{
    shuffled_indices.reserve(num_samples * num_sets);
    std::vector<int> indices;

    for(int j = 0; j < num_samples; j++){
        indices.push_back(j);
    }

    for(int p = 0; p < num_sets; p++){
        std::random_shuffle(indices.begin(), indices.end());

        for(int j = 0; j < num_samples; j++){
            shuffled_indices.push_back(indices[j]);
        }
    }
}

void Sampler::shuffle_samples()
{
}


//zufälligen Punkt der gesampled werden soll wird ausgegeben
QPoint Sampler::sample_unit_square()
{
    if(count % num_samples == 0){
        jump = (rand() % num_sets) * num_samples;
    }

    return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}
