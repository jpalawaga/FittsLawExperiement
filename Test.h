#ifndef __TEST_H
#define __TEST_H

#include "DataPoint.h"
#include <QVector>
#include "ExperimentSettings.h"

class QPoint;

class Test {

    public:
        Test(ExperimentSettings e);
        Test() {}
        QVector<DataPoint> clicks;
        void insertClick(QPoint p, int time);
        ExperimentSettings getSettings() { return expSettings; }

    private:
        ExperimentSettings expSettings;
};

#endif
