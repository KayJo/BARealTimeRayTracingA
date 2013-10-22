#ifndef SAMPLER_H
#define SAMPLER_H
#include <vector>
#include <QVector3D>
#include <QPoint>
class Sampler
{
public:
    Sampler();
    Sampler(int ns);
    Sampler(int ns, int sets);
    Sampler(const Sampler& spl);
    virtual ~Sampler();

    virtual Sampler* clone() const = 0;
    virtual void generate_samples() = 0;

    void setup_shuffled_indices();
    void shuffle_samples();
    QPoint sample_unit_square();

    void set_num_samples(int ns);
    void set_num_sets(int sets);
    int get_num_samples();

protected:
    int num_samples;
    int num_sets;
    std::vector<QPoint> samples;
    std::vector<int> shuffled_indices;
    int count;
    int jump;

};

inline void Sampler::set_num_samples(int ns){
    num_samples = ns;
}

inline void Sampler::set_num_sets(int sets){
    num_sets = sets;
}

inline int Sampler::get_num_samples(){
    return num_samples;
}

#endif // SAMPLER_H
