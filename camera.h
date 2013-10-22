#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QMatrix4x4>

class World;    //World Klasse kann nicht inkludiert werden, da World Klasse einen Kamera Pointer besitzt

class Camera
{
public:
    Camera();
    Camera(const Camera& ca);
    virtual ~Camera();

    virtual Camera* clone() const = 0;
    void set_eye(const QVector3D _eye);
    void set_eye(const float x, const float y, const float z);
    void set_lookat(const QVector3D _lookat);
    void set_lookat(const float x, const float y, const float z);
    void set_up(const float x, const float y, const float z);
    void set_u(const float x, const float y, const float z);
    void set_v(const float x, const float y, const float z);
    void set_w(const float x, const float y, const float z);
    void set_exposure_time(const double expTime);
    void compute_uvw();
//    virtual void render_scene(World& w) = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
    virtual bool isZoomable() = 0;
    virtual float getZoomFactor();
    virtual QVector3D ray_direction(const QPoint& p) = 0;
    double getExposureTime();

    QVector3D getEye();
    QVector3D getLookat();
    QVector3D getUp();


protected:
    QVector3D eye;
    QVector3D lookat;
    QVector3D up;
    QVector3D u;
    QVector3D v;
    QVector3D w;
    double exposure_time;
//    QMatrix4x4 uvw;
};

inline void Camera::set_eye(const QVector3D _eye)
{
    eye = _eye;
}

inline void Camera::set_eye(const float x, const float y, const float z){
    eye.setX(x);
    eye.setY(y);
    eye.setZ(z);
}

inline void Camera::set_lookat(const QVector3D _lookat)
{
    lookat = _lookat;
}

inline void Camera::set_lookat(const float x, const float y, const float z){
    lookat.setX(x);
    lookat.setY(y);
    lookat.setZ(z);
}

inline void Camera::set_up(const float x, const float y, const float z){
    up.setX(x);
    up.setY(y);
    up.setZ(z);
}

inline void Camera::set_u(const float x, const float y, const float z){
    u.setX(x);
    u.setY(y);
    u.setZ(z);
}

inline void Camera::set_v(const float x, const float y, const float z){
    v.setX(x);
    v.setY(y);
    v.setZ(z);
}

inline void Camera::set_w(const float x, const float y, const float z){
    w.setX(x);
    w.setY(y);
    w.setZ(z);
}

inline void Camera::set_exposure_time(const double expTime){
    exposure_time = expTime;
}

#endif // CAMERA_H
