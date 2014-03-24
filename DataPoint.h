#ifndef __DATAPOINT_H
#define __DATAPOINT_H

#include <QPoint>

struct DataPoint{

    QPoint point;
    int time;
    bool hit;

    DataPoint();
    DataPoint(QPoint p, int time, bool hit);
};

#endif
