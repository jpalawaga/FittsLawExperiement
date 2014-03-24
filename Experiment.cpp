#include <QtGui>
#include <QSqlQuery>
#include <QSqlError>
#include "Experiment.h"
#include "Test.h"

Experiment::Experiment(FittsWidget * fw, QSqlDatabase database) {
    db = database;
    widget = fw;
    experimentNumber = 0;
    bool ok;
    bool queryStatus = false;
    name = QInputDialog::getText(0, "Name", "Please enter your name:", QLineEdit::Normal, "", &ok);
    
    QSqlQuery query(db);
    if (db.isValid() && db.open()) {

        qDebug() << name;
        query.prepare("INSERT INTO volunteers (name) VALUES('Will')");
        query.bindValue(0, name);
        queryStatus = query.exec();
        qDebug() << query.lastQuery();
        QSqlError e;
        e=query.lastError();
        qDebug() << e.text();
    } else {
        qDebug() << "DB Not open/Valid";
        QMessageBox::warning(this, tr("Done"), tr("DB not open."));
    }

    if (queryStatus) {
        qDebug() << "STATUS";
        volunteerId = query.lastInsertId().toInt();
    }
}

void Experiment::run() {
    if (experimentNumber < tests.size()) {
        widget->runExperiment(tests[experimentNumber].getSettings());
        experimentNumber++;
    } else {
        QMessageBox::information(this, tr("Done"), tr("Testing is complete."));
        insertToDatabase();
    }
}

void Experiment::insertToDatabase() {
    for (int j = 0; j < tests.size(); j++) {
        for (int k = 0; k < tests[j].clicks.size(); k++) {
            QSqlQuery query(db);
            if (db.open()) {
                query.prepare("INSERT INTO experiments(volunteer_id, testno, size, distance, mouse_x, mouse_y, hit, time) VALUES(:id, :testno, :s, :d, :x, :y, :hit, :time)");
                query.bindValue(":id", volunteerId);
                query.bindValue(":testno", j);
                query.bindValue(":s", tests[j].getSettings().getSize());
                query.bindValue(":d", tests[j].getSettings().getDistance());
                query.bindValue(":x", tests[j].clicks[k].point.x());
                query.bindValue(":y", tests[j].clicks[k].point.y());
                query.bindValue(":hit", tests[j].clicks[k].hit);
                query.bindValue(":time", tests[j].clicks[k].time);
                query.exec();
                qDebug() << query.lastQuery();
            } else {
                QMessageBox::warning(this, tr("Done"), tr("DB not open."));
            } 
        }
    }
}

void Experiment::addExperiment(ExperimentSettings s) {
    Test t(s);
    tests.push_back(t);
}

void Experiment::registerClick(QPoint p, int t, bool h) {
    tests[experimentNumber-1].insertClick(p, t, h);
}

