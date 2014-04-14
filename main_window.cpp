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

    //                                          width  distance
    ExperimentSettings tra1("Training - Easy",    250, 600, ExperimentSettings::BYHITS, 30);
    qDebug() << experiment->calculateX(600, 200);
    ExperimentSettings tra2("Training - Medium",  100, 320, ExperimentSettings::BYHITS, 30);
    qDebug() << experiment->calculateX(300, 70);
    ExperimentSettings tra3("Training - Hard",  50, 400, ExperimentSettings::BYHITS, 30);
    qDebug() << experiment->calculateX(400, 50);
    ExperimentSettings exp1("Test One",           100, 320, ExperimentSettings::BYCLICKS, 30);
    ExperimentSettings exp2("Test Two",          100, 320, ExperimentSettings::BYCLICKS, 30);
    ExperimentSettings exp3("Test Three",        100,  320, ExperimentSettings::BYCLICKS, 30);
    experiment->addTrainingTrial(tra1);
    experiment->addTrainingTrial(tra2);
    experiment->addTrainingTrial(tra3);
    experiment->addTestTrial(exp1);
    experiment->addTestTrial(exp2);
    experiment->addTestTrial(exp3);
    experiment->run();

    db.close();
}

