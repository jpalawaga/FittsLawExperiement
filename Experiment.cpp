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
    bool queryStatus = false;
    name = QInputDialog::getText(0, "Name", "Please enter your name:", QLineEdit::Normal, "", &ok);
    query = QSqlQuery(db);

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
                if (volunteerId == 0) {
                    query.prepare("INSERT INTO volunteers (name) VALUES(:name)");
                    query.bindValue(":name", name);
                    query.exec();
                    volunteerId = query.lastInsertId().toInt();
                }
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

