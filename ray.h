#ifndef RAY_H
#define RAY_H
#include <QVector3D>

class Ray
{
public:
    QVector3D o;
    QVector3D d;

    Ray();
    Ray(const QVector3D origin, const QVector3D direction);
    Ray(const Ray& ray);
    virtual ~Ray();




};

#endif // RAY_H
