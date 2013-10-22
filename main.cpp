//#include "renderwindow.h"
#include <QApplication>
#include "world.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    RenderWindow w;
    World w;
    w.build();
    w.show();
//    w.camera_ptr->render_scene(w);
//    w.show();
    
    return a.exec();
}
