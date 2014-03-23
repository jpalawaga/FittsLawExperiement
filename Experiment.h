#ifndef __EXPERIMENT_H
#define __EXPERIMENT_H

#include <QVector>
#include "Test.h"
#include "FittsWidget.h"

class QString; 

class Experiment {

    public:
        Experiment(FittsWidget * fw);
        QVector<Test> tests;

        void run();
        void addExperiment(ExperimentSettings settings);

    private:
        QString name;
        FittsWidget * widget;
};

#endif
