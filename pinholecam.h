#ifndef PINHOLECAM_H
#define PINHOLECAM_H
#include "camera.h"

class PinholeCam : public Camera
{
public:
    PinholeCam();
    PinholeCam(const float distance, const float z);
    PinholeCam(const PinholeCam& pc);
    virtual ~PinholeCam();

    virtual Camera* clone() const;
//    virtual void render_scene(World &w);
    QVector3D ray_direction(const QPoint& p);

    void set_d(const float distance);
    void set_zoom(const float z);
    virtual void zoomIn();
    virtual void zoomOut();
    virtual bool isZoomable();
    virtual float getZoomFactor();


private:
    float d;    //Abstand zur View Plane
    float zoom; //Zoom Faktor
};


inline void PinholeCam::set_d(const float distance){
    d = distance;
}

inline void PinholeCam::set_zoom(const float z){
    zoom = z;
}

#endif // PINHOLECAM_H
