#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QWaitCondition>
#include "rgb.h"


const double PI = 3.1415926535897932384;
const double INV_PI = 0.3183098861837906715;
const double kHugeValue = 1.0E10;
const double ZEHN_GRAD = 10 * (PI / 180);
const int MAX_RADIUS = 200;
const int MAX_MRADIUS = -200;
const int EINHEIT = 20;


const RGB white(1.0);
const RGB black(0.0);
//QWaitCondition eventFinished;
//QMutex mutex;


#endif // CONSTANTS_H
