#include <QtGui>
#include "Experiment.h"
#include "Test.h"

Experiment::Experiment(FittsWidget * fw, QSqlDatabase * database) {
    db = database;
    widget = fw;
    experimentNumber = 0;
    bool ok;
    name = QInputDialog::getText(0, "Name", "Please enter your name:", QLineEdit::Normal, "", &ok);
}

void Experiment::run() {
    if (experimentNumber < tests.size()) {
        widget->runExperiment(tests[experimentNumber].getSettings());
        experimentNumber++;
    } else {
        QMessageBox::information(this, tr("Done"), tr("Testing is complete."));

    }
}

void Experiment::addExperiment(ExperimentSettings s) {
    Test t(s);
    tests.push_back(t);
}

void Experiment::registerClick(QPoint p, int t, bool h) {
    tests[experimentNumber-1].insertClick(p, t, h);
}

