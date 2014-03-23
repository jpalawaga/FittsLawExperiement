#include <QtGui>
#include "Experiment.h"
#include "Test.h"

Experiment::Experiment(FittsWidget * fw) {
    widget = fw;    
    bool ok;
    name = QInputDialog::getText(0, "Name", "Please enter your name:", QLineEdit::Normal, "name", &ok);
}

void Experiment::run() {
    for (int i = 0; i < tests.size(); i++) {
        widget->runExperiment(tests[0].getSettings());
    }
}

void Experiment::addExperiment(ExperimentSettings s) {
    Test t(s);
    tests.push_back(t);
}

