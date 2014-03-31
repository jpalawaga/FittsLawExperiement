// Name:  James Palawaga
//  SN:    001158466
//    
//  MainWindow implementation for Part 3 of the assignment.

#include <QtGui>
#include "main_window.h"
#include "FittsWidget.h"
#include "ExperimentSettings.h"
#include "Experiment.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QSqlDatabase db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    setCentralWidget(fWid = new FittsWidget(parent));
    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    
    Experiment * experiment = new Experiment(fWid, db);
    connect(fWid, SIGNAL(experimentComplete()), experiment, SLOT(run()));
    connect(fWid, SIGNAL(buttonClicked(QPoint, int, bool)), experiment, SLOT(registerClick(QPoint, int, bool)));

//@TODO Before each test (read; Not training), output no. ms in minute / timeCalc value.
//@TODO Output accuracy absed on number of clicks vs number of successful clicks.
//@TODO MAYBE: randomize the experiement run order.i
//@TODO Three training sessions (maybe making it know automatically how many trainign sessions exist).
    ExperimentSettings exp("Training", 100, 150, ExperimentSettings::BYHITS, 25);
    ExperimentSettings exp1("Training 2", 100, 300, ExperimentSettings::BYHITS, 25);
    ExperimentSettings exp2("Test 1", 100, 250, ExperimentSettings::BYCLICKS, 10);
    ExperimentSettings exp3("Test2", 100, 60, ExperimentSettings::BYCLICKS, 10);
    experiment->addExperiment(exp);
    experiment->addExperiment(exp1);
    experiment->addExperiment(exp2);
    experiment->addExperiment(exp3);
    experiment->run();

    db.close();
}

