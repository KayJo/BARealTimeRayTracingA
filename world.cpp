#include "world.h"
#include <vector>
#include <cmath>
#include <QPainter>
#include <QTime>
#include <QString>
#include <QKeyEvent>
#include <QMatrix4x4>
#include "ambient.h"
#include "directional.h"
#include "constants.h"
#include "whittedtracer.h"
#include "sphere.h"
#include "plane.h"
#include "phong.h"
#include "pinholecam.h"
#include "pointlight.h"
#include "reflective.h"
#include "transparent.h"
#include "light.h"



World::World(QWidget *parent)
    : QWidget(parent),
      camera_ptr(NULL),
      tracer_ptr(NULL),
      ambient_ptr(new Ambient),
      background_color(black)
{
//    setWindowTitle("Ray Tracer C++");

//    resize(550,400);
    ticker.start(25,this);
    counter = 0;
}

World::World(const World &_w) :
    vp(_w.vp),
    background_color(_w.background_color)
{
    if(_w.camera_ptr) {
        camera_ptr = _w.camera_ptr->clone();
    } else {
        camera_ptr = NULL;
    }

    if(_w.tracer_ptr) {
        tracer_ptr = _w.tracer_ptr->clone();
    } else {
        tracer_ptr = NULL;
    }

    if(_w.ambient_ptr) {
        ambient_ptr = _w.ambient_ptr->clone();
    } else {
        ambient_ptr = NULL;
    }
}

World::~World()
{
    if(tracer_ptr){
//        tracer_ptr->quit();
//        tracer_ptr->wait();
        delete tracer_ptr;
        tracer_ptr = NULL;
    }

    if(ambient_ptr){
        delete ambient_ptr;
        ambient_ptr = NULL;
    }

    if(camera_ptr){
        delete camera_ptr;
        camera_ptr = NULL;
    }

    delete_objects();
    delete_lights();
}

World* World::clone() const
{
    return new World(*this);
}

void World::timerEvent(QTimerEvent *)
{
    showFps();
}

void World::paintEvent(QPaintEvent *event)
{

//    setWindowTitle("Ray Tracer C++");

    resize(vp.hres,vp.vres);
    //Hier könnte ich den Ray Tracer Thread starten
    //Bin ich mir noch unsicher ob das so richtig ist hier
    //den Thread zu starten


//    camera_ptr->render_scene(*this);
    QPainter painter(this);
    painter.drawImage(windowSize,image);

//    counter++;
//    qDebug() << "Anzahl Frames: " << counter;
//    update();
}

void World::build(){

    vp.set_horizontal_resolution(400);
    vp.set_vertical_resolution(400);
    vp.set_samples(1);
    vp.set_pixel_size(0.5);
    vp.set_max_depth(20);

    image = QImage(vp.hres,vp.vres,QImage::Format_RGB32);
    tmpImage = QImage(vp.hres, vp.vres, QImage::Format_RGB32);
    windowSize.setHeight(vp.vres);
    windowSize.setWidth(vp.hres);

    Ambient* amb_ptr = new Ambient;
    amb_ptr->set_color(white);
    amb_ptr->set_radiance_factor(1.0);
    set_ambient_light(amb_ptr);


    tracer_ptr = new WhittedTracer(this);

    PinholeCam* cam_ptr = new PinholeCam;
    cam_ptr->set_eye(0,0,200);
    cam_ptr->set_lookat(0,0,0);
    cam_ptr->set_up(0,1,0);
    cam_ptr->set_exposure_time(1.0);
    cam_ptr->set_d(500.0);
    cam_ptr->compute_uvw();
    set_camera(cam_ptr);

//    Directional* dir_ptr = new Directional;
//    dir_ptr->set_color(white);
//    dir_ptr->set_radiance_factor(3.0);
//    dir_ptr->set_direction(QVector3D(1,1,0).normalized());
//    add_light(dir_ptr);

    PointLight* pointLight_ptr = new PointLight;
    pointLight_ptr->set_color(white);
    pointLight_ptr->set_radiance_factor(3.0);
    pointLight_ptr->set_location(QVector3D(-50,100,0));
    add_light(pointLight_ptr);

    RGB yellow(1, 1, 0);										// yellow
//    RGB brown(0.71, 0.40, 0.16);								// brown
    RGB darkGreen(0.0, 0.41, 0.41);							// darkGreen
//    RGB orange(1, 0.75, 0);									// orange
//    RGB green(0, 0.6, 0.3);									// green
//    RGB lightGreen(0.65, 1, 0.30);								// light green
//    RGB darkYellow(0.61, 0.61, 0);								// dark yellow
//    RGB lightPurple(0.65, 0.3, 1);								// light purple
//    RGB darkPurple(0.5, 0, 1);									// dark purple
//    RGB grey(0.25);
    RGB blue(0,0.75,1);
    RGB red(1.0,0.0,0.0);
    RGB tmp(0.75,0.75,0);


    Phong* phong_ptr = new Phong;
    phong_ptr->set_kd(0.6);
    phong_ptr->set_cd(red);
    phong_ptr->set_ks(0.2);
    phong_ptr->set_exp(100);

    Sphere* sphere_ptr = new Sphere;
    sphere_ptr->set_center(0, 0, 0);
    sphere_ptr->set_radius(10);
    sphere_ptr->set_material(phong_ptr);
    add_object(sphere_ptr);

    Reflective* ref_ptr = new Reflective;
    ref_ptr->set_kd(0.5);
    ref_ptr->set_cd(tmp);
    ref_ptr->set_ks(0.15);
    ref_ptr->set_exp(100);
    ref_ptr->setKR(0.75);
    ref_ptr->setCR(white);

    Sphere* sphereA_ptr = new Sphere;
    sphereA_ptr->set_center(25,10,0);
    sphereA_ptr->set_radius(10);
    sphereA_ptr->set_material(ref_ptr);
    add_object(sphereA_ptr);

    Transparent* trans_ptr = new Transparent;
    trans_ptr->set_ks(0.5);
    trans_ptr->set_exp(200);
    trans_ptr->setIOR(1.5);
    trans_ptr->setKR(0.1);
    trans_ptr->setKT(0.9);

    Sphere* sphereB_ptr = new Sphere;
    sphereB_ptr->set_center(-25, 5, 25);
    sphereB_ptr->set_radius(10);
    sphereB_ptr->set_material(trans_ptr);
    add_object(sphereB_ptr);



    Phong* phong_ptr1 = new Phong;
    phong_ptr1->set_kd(0.40);
    phong_ptr1->set_cd(darkGreen);
    phong_ptr1->set_ks(0.75);
    phong_ptr1->set_exp(300);

    Plane* plane_ptr = new Plane;
    plane_ptr->set_a(0,-10,0);
    plane_ptr->set_normal(QVector3D(0,1,0).normalized());
    plane_ptr->set_material(phong_ptr1);
    add_object(plane_ptr);

    Phong* phongA_ptr1 = new Phong;
    phongA_ptr1->set_kd(0.40);
    phongA_ptr1->set_cd(blue);
    phongA_ptr1->set_ks(0.75);
    phongA_ptr1->set_exp(300);

    Plane* planeA_ptr = new Plane;
    planeA_ptr->set_a(0,-10,-50);
    planeA_ptr->set_normal(QVector3D(0,0,1).normalized());
    planeA_ptr->set_material(phongA_ptr1);
    add_object(planeA_ptr);

    tracer_ptr->restartTracing();
}

void World::open_window(int hres, int vres)
{
    //WIRD VON PINHOLECAM AUFGERUFEN IN DER FUNKTION RENDER_SCENE
//    setWindowTitle("Ray Tracer C++");

    resize(hres,vres);
//    this->show();
}

void World::display_pixel(const int row, const int col, const RGB &cp)
{

    QColor mapped_color;

    if(vp.show_out_of_gammut){
        mapped_color = clamp_to_color(cp);
    } else {
        mapped_color = max_to_one(cp);
    }

    if(vp.gamma != 1.0){
        mapped_color.setRgbF(pow(mapped_color.redF(), vp.inv_gamma),
                             pow(mapped_color.greenF(), vp.inv_gamma),
                             pow(mapped_color.blueF(), vp.inv_gamma));
    }


    int rowTmp = -row + (vp.vres-1);

    //Hier muss noch der Code geschrieben werden um den pixel darzustellen
    //dies wird dann mithilfe der row, col und mapped_color variablen geschehen
    //

    //hier wird dann das QImage gefüllt
    //es muss irgendwie überprüft werden
    //wann das QImage gefüllt ist
    //geht wohl nur wenn row und col
    //überprüft werden und diese genauso
    //groß sind wie v.hres und v.vres
    //vielleicht sogar -1
    //dann muss ein update geschehen

    tmpImage.setPixel(col, rowTmp,mapped_color.rgba());

    if(col == (vp.hres - 1) && row == (vp.vres - 1)) {
        //Hier wird vielleicht auch ein fehler auftreten
        image = tmpImage;
        update();
    }
//Alte Version wo noch renderScene genutzt wurde
//    QPainter painter(this);

//    painter.setPen(mapped_color);
//    painter.drawPoint(col, rowTmp);
}

ShadeRec World::hit_objects(const Ray &ray)
{
    ShadeRec sr(*this);
    double t;
    QVector3D normal;
    QVector3D local_hit_point;
    float tmin = kHugeValue;
    int num_objects = objects.size();

    for(int j = 0; j < num_objects; j++){
        if(objects[j]->hit(ray, t, sr) && (t < tmin)){
            sr.hit_an_object = true;
            tmin = t;
            sr.material_ptr = objects[j]->get_material();
            sr.hit_point = ray.o + t * ray.d;
            normal = sr.normal;
            local_hit_point = sr.local_hit_point;
        }

    }

    if(sr.hit_an_object){
        sr.t = tmin;
        sr.normal = normal;
        sr.local_hit_point = local_hit_point;
    }

    return sr;
}

QColor World::max_to_one(const RGB &c) const
{
    float max_value = std::max(c.r, std::max(c.g, c.b));
    RGB rgb;
    QColor qc;

    if(max_value > 1.0){

        rgb = c / max_value;
        qc.setRgbF(rgb.r,rgb.g,rgb.b);

        return qc;
    } else {
        qc.setRgbF(c.r,c.g,c.b);
        return qc;
    }
}


QColor World::clamp_to_color(const RGB &raw_color) const
{
    QColor c;
    c.setRgbF(raw_color.r,raw_color.g, raw_color.b);

    if(raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0){
        c.setRgbF(1.0, 0.0, 0.0);
    }

    return c;
}

void World::showFps() {
    static QTime frameTick;
    static int totalFrame = 0;
    if (!(totalFrame & 31)) {
        int elapsed = frameTick.elapsed();
        frameTick.start();
        int fps = 32 * 1000 / (1 + elapsed);
        setWindowTitle(QString("Ray Tracer (%1 FPS)").arg(fps));
    }
    totalFrame++;
}

void World::delete_objects()
{
    int n_obj = objects.size();

    for(int i = 0; i < n_obj; i++){
        delete objects[i];
        objects[i] = NULL;
    }

    objects.erase(objects.begin(), objects.end());
}

void World::delete_lights()
{
    int n_lights = lights.size();

    for(int i = 0; i < n_lights; i++){
        delete lights[i];
        lights[i] = NULL;
    }

    lights.erase(lights.begin(), lights.end());
}

QVector3D World::rotateYAxe(float _angle, const QVector3D &_ver)
{


    return QVector3D(_ver.x() * cos(_angle) + _ver.z() * sin(_angle),
                     _ver.y(),
                     _ver.x() * -sin(_angle) + _ver.z() * cos(_angle));

}

QVector3D World::rotateXAxe(float _angle, const QVector3D &_ver)
{


    return QVector3D(_ver.x(),
                     _ver.y() * cos(_angle) + _ver.z() * -sin(_angle),
                     _ver.y() * sin(_angle) + _ver.z() * cos(_angle));
}

void World::keyPressEvent(QKeyEvent *event)
{
    event->accept();
    QVector3D tmpEye = camera_ptr->getEye();
    QVector3D tmpLookat = camera_ptr->getLookat();
    if(event->key() == Qt::Key_Right) {

        camera_ptr->set_eye(tmpEye.x() + 10,tmpEye.y(), tmpEye.z());
        camera_ptr->set_lookat(tmpLookat.x() + 10, tmpLookat.y(), tmpLookat.z());
        camera_ptr->compute_uvw();

    }
    if(event->key() == Qt::Key_Left) {

        camera_ptr->set_eye(tmpEye.x() - 10,tmpEye.y(), tmpEye.z());
        camera_ptr->set_lookat(tmpLookat.x() - 10, tmpLookat.y(), tmpLookat.z());
        camera_ptr->compute_uvw();
    }
    if(event->key() == Qt::Key_Up) {
        camera_ptr->set_eye(tmpEye.x(),tmpEye.y() + 10, tmpEye.z());
        camera_ptr->set_lookat(tmpLookat.x(), tmpLookat.y() + 10, tmpLookat.z());
        camera_ptr->compute_uvw();

    }
    if(event->key() == Qt::Key_Down) {

        camera_ptr->set_eye(tmpEye.x(),tmpEye.y() - 10, tmpEye.z());
        camera_ptr->set_lookat(tmpLookat.x(), tmpLookat.y() - 10, tmpLookat.z());
        camera_ptr->compute_uvw();

    }
    if(event->key() == Qt::Key_W) {

        camera_ptr->set_eye(rotateXAxe(-ZEHN_GRAD,tmpEye));
        camera_ptr->set_lookat(rotateXAxe(-ZEHN_GRAD, tmpLookat));
        camera_ptr->compute_uvw();
    }
    if(event->key() == Qt::Key_S) {

        camera_ptr->set_eye(rotateXAxe(ZEHN_GRAD, tmpEye));
        camera_ptr->set_lookat(rotateXAxe(ZEHN_GRAD, tmpLookat));
        camera_ptr->compute_uvw();
    }
    if(event->key() == Qt::Key_D) {
        camera_ptr->set_eye(rotateYAxe(ZEHN_GRAD, tmpEye));
        camera_ptr->set_lookat(rotateYAxe(ZEHN_GRAD, tmpLookat));
        camera_ptr->compute_uvw();
    }
    if(event->key() == Qt::Key_A) {
        camera_ptr->set_eye(rotateYAxe(-ZEHN_GRAD, tmpEye));
        camera_ptr->set_lookat(rotateYAxe(-ZEHN_GRAD, tmpLookat));
        camera_ptr->compute_uvw();
    }
    if(event->key() == Qt::Key_Plus) {
        camera_ptr->zoomIn();
    }
    if(event->key() == Qt::Key_Minus) {
        camera_ptr->zoomOut();

    }
    if(event->key() == Qt::Key_Z) {
        for(int i = 0; i < lights.size(); i++) {
            lights[i]->castsShadows() ?
                        lights[i]->setShadows(false) :
                        lights[i]->setShadows(true);
        }
        ambient_ptr->castsShadows() ?
                    ambient_ptr->setShadows(false) :
                    ambient_ptr->setShadows(true);
    }
    if(event->key() == Qt::Key_T) {
        ++vp.max_depth;
    }
    if(event->key() == Qt::Key_R) {
        --vp.max_depth;
    }
    update();
    tracer_ptr->restartTracing();
}
