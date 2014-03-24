#ifndef __EXPERIMENT_H
#define __EXPERIMENT_H

#include <QVector>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Test.h"
#include "FittsWidget.h"

class QString;

class Experiment : public QWidget {

    Q_OBJECT

    public:
        Experiment(FittsWidget * fw, QSqlDatabase db);
        QVector<Test> tests;

        void addExperiment(ExperimentSettings settings);

    public slots:
        void run();
        void registerClick(QPoint p, int t, bool h);

    private:
        int experimentNumber;
        int volunteerId;
        QSqlQuery query;
        QString name;
        FittsWidget * widget;
        QSqlDatabase db;
        void insertToDatabase();
};

#endif
