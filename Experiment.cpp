#include <QtGui>
#include "Experiment.h"
#include "Test.h"

Experiment::Experiment(FittsWidget * fw) {
    widget = fw;
    experimentNumber = 0;
    bool ok;
    name = QInputDialog::getText(0, "Name", "Please enter your name:", QLineEdit::Normal, "name", &ok);
}

void Experiment::run() {
    qDebug() << "RECEIVED";
    if (experimentNumber < tests.size()) {
        widget->runExperiment(tests[experimentNumber].getSettings());
        experimentNumber++;
    } else {
        qDebug() << "END.";
    }
}

void Experiment::addExperiment(ExperimentSettings s) {
    Test t(s);
    tests.push_back(t);
}

void Experiment::registerClick(QPoint p, int t, bool h) {
    tests[experimentNumber].insertClick(p, t, h);
}

