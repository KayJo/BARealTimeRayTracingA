#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <QColor>
#include <QWidget>
#include <QBasicTimer>
#include "viewplane.h"
#include "camera.h"
#include "raytracer.h"
//#include "light.h"
#include "geometry.h"
#include "ray.h"
#include "rgb.h"
//#include "shaderec.h"

class Geometry;
class Light;
class ShadeRec;

class World : public QWidget
{
    Q_OBJECT
public:

    //Hier muss noch eine QImage variable gesetzt werden
    //Welche im Build oder im Konstruktor erzeugt wird.

    ViewPlane vp;
    Camera* camera_ptr;
    RayTracer* tracer_ptr;
    Light* ambient_ptr;
    RGB background_color;
    std::vector<Geometry*> objects;
    std::vector<Light*> lights;
    QImage image;
    QImage tmpImage;
    QRect windowSize;
    int counter;

    World(QWidget *parent = 0);
    World(const World& _w);
    World* clone() const;
    virtual ~World();

    void add_object(Geometry* obj_ptr);
    void add_light(Light* li_ptr);
    void set_ambient_light(Light* li_ptr);
    void set_camera(Camera* cam_ptr);


    void build();
    void display_pixel(const int row, const int col,const RGB& cp);
    void open_window(int hres, int vres);
    ShadeRec hit_objects(const Ray& ray);
    QColor max_to_one(const RGB& c) const;
    QColor clamp_to_color(const RGB& raw_color) const;

private:

    QBasicTimer ticker;
    QVector3D translateXAxe(const QVector3D& _lookat, const QVector3D& _eye, float _x);
    QVector3D translateYAxe(const QVector3D& _lookat, const QVector3D& _eye, float _y);
    QVector3D rotateYAxe(float _angle, const QVector3D & _ver);
    QVector3D rotateXAxe(float _angle, const QVector3D& _ver);
    void showFps();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *);
    virtual void keyPressEvent(QKeyEvent *event);


private:

    void delete_objects();
    void delete_lights();
};

inline void World::add_object(Geometry *obj_ptr){
    objects.push_back(obj_ptr);
}

inline void World::add_light(Light *li_ptr){
    lights.push_back(li_ptr);
}

inline void World::set_ambient_light(Light* li_ptr){
    ambient_ptr = li_ptr;
}

inline void World::set_camera(Camera *cam_ptr){
    camera_ptr = cam_ptr;
}

#endif // WORLD_H
