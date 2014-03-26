#include <unistd.h>
#include <QtGui>
#include <QSqlQuery>
#include <QSqlError>
#include "Experiment.h"
#include "Test.h"

Experiment::Experiment(FittsWidget * fw, QSqlDatabase database) {
    db = database;
    widget = fw;
    experimentNumber = 0;
    volunteerId = 0;
    bool ok;
    name = QInputDialog::getText(0, "Name", "Please enter your name:", QLineEdit::Normal, "", &ok);
    if (db.open()) {
        QSqlQuery query(db);
        if (volunteerId == 0) {
            query.prepare("INSERT INTO volunteers (name) VALUES(:name)");
            query.bindValue(":name", name);
            query.exec();
            volunteerId = query.lastInsertId().toInt();
            query.clear();
        }
    } else {
        QMessageBox::warning(this, tr("Done"), tr("DB not open."));
    }
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
    if (db.open()) {
        QSqlQuery query(db);
        QString q = QString("INSERT INTO experiments(volunteer_id, testno, size, distance, mouse_x, mouse_y, hit, time) VALUES(%1, %2, %3, %4, %5, %6, %7, %8)").arg(volunteerId).arg(experimentNumber-1).arg(tests[experimentNumber-1].getSettings().getSize()).arg( tests[experimentNumber-1].getSettings().getDistance()).arg(p.x()).arg(p.y()).arg(h).arg(t);
        query.exec(q);
        // @TODO Proper error handling
        //qDebug() << q;
        //QSqlError e = query.lastError();
        //qDebug() << e.text();
        query.clear();
    }
}
