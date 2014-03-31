#include <QtGui>
#include <QPoint>
#include "Test.h"
#include "ExperimentSettings.h"
#include "DataPoint.h"

Test::Test() {
    expSettings = ExperimentSettings("Default Test");
}

Test::Test(ExperimentSettings e) {
    expSettings = e;
    numberOfClicks = numberOfHits = 0;
}

void Test::insertClick(QPoint p, int time, bool hit) {
    DataPoint temp(p, time, hit);
    clicks.push_back(temp);
    numberOfClicks++;
    if (hit)
        numberOfHits++;
}

double Test::getAccuracy() {
    qDebug() << numberOfHits << " / " << numberOfClicks;
    return numberOfHits * 1.0  / numberOfClicks;
}

