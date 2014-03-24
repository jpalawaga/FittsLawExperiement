#include "DataPoint.h"

DataPoint::DataPoint() {
}

DataPoint::DataPoint(QPoint p, int t, bool h) {
    point = p;
    time = t;
    hit = h;
}
