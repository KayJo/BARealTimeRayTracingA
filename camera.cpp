#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(const Camera &ca) :
    eye(ca.eye),
    lookat(ca.lookat),
    up(ca.up),u(ca.u),
    v(ca.v),
    w(ca.w),
    exposure_time(ca.exposure_time)
{
}

Camera::~Camera()
{
}


void Camera::compute_uvw()
{
    w = eye - lookat;
    w.normalize();
    u = QVector3D::crossProduct(up, w);     //so ist es richtig: up,w
    u.normalize();
    v = QVector3D::crossProduct(w, u);

    if(eye.x() == lookat.x() && eye.z() == lookat.z() && eye.y() > lookat.y()) {
        u = QVector3D(0,0,1);
        v = QVector3D(1,0,0);
        w = QVector3D(0,1,0);
    }

    if(eye.x() == lookat.x() && eye.z() == lookat.z() && eye.y() < lookat.y()) {
        u = QVector3D(1,0,0);
        v = QVector3D(0,0,1);
        w = QVector3D(0,-1,0);
    }

//    uvw.lookAt(eye, lookat, up);
}

QVector3D Camera::getEye()
{
    return eye;
}

QVector3D Camera::getLookat()
{
    return lookat;
}

QVector3D Camera::getUp()
{
    return up;
}

float Camera::getZoomFactor()
{
    return 1.0;
}

double Camera::getExposureTime()
{
    return exposure_time;
}


