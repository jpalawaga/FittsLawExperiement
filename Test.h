#ifndef __TEST_H
#define __TEST_H

#include "DataPoint.h"
#include <QVector>
#include "ExperimentSettings.h"

class QPoint;

class Test {

    public:
        Test(ExperimentSettings e);
        Test();
        QVector<DataPoint> clicks;
        void insertClick(QPoint p, int time, bool h);
        ExperimentSettings getSettings() { return expSettings; }
        double getAccuracy();

    private:
        ExperimentSettings expSettings;
        int numberOfClicks;
        int numberOfHits;
};

#endif
