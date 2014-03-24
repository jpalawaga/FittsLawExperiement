#ifndef __EXPERIMENT_H
#define __EXPERIMENT_H

#include <QVector>
#include <QtGui>
#include <QSqlDatabase>
#include "Test.h"
#include "FittsWidget.h"

class QString;

class Experiment : public QWidget {

    Q_OBJECT

    public:
        Experiment(FittsWidget * fw, QSqlDatabase * db);
        QVector<Test> tests;

        void addExperiment(ExperimentSettings settings);

    public slots:
        void run();
        void registerClick(QPoint p, int t, bool h);

    private:
        int experimentNumber;
        QString name;
        FittsWidget * widget;
        QSqlDatabase * db;
};

#endif
