#include <QtGui>
#include <QPoint>
#include "Test.h"
#include "ExperimentSettings.h"
#include "DataPoint.h"

Test::Test(ExperimentSettings e) {
    expSettings = e;
}

void Test::insertClick(QPoint p, int time) {
    DataPoint temp(p, time);
    clicks.push_back(temp);
}

