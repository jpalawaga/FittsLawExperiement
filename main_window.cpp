// Name:  James Palawaga
//  SN:    001158466
//    
//  MainWindow implementation for Part 3 of the assignment.

#include <QtGui>
#include "main_window.h"
#include "FittsWidget.h"
#include "ExperimentSettings.h"
#include "Experiment.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setCentralWidget(fWid = new FittsWidget(parent));
    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    
    Experiment * experiment = new Experiment(fWid);
    connect(fWid, SIGNAL(experimentComplete()), experiment, SLOT(run()));
    connect(fWid, SIGNAL(buttonClicked(QPoint, int, bool)), experiment, SLOT(registerClick(QPoint, int, bool)));

    ExperimentSettings exp(10, 150, ExperimentSettings::BYHITS, 10);
    ExperimentSettings exp2(10, 250, ExperimentSettings::BYCLICKS, 10);
    experiment->addExperiment(exp);
    experiment->addExperiment(exp2);
    experiment->run();
}

bool MainWindow::writeFile(const QString &filename, const QString &text) {

    QFile file(filename);
        
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Unable to save"), 
            tr("Cannot write file %1: %2").arg(filename).arg(file.errorString()));
        return false;
    }
          
    QTextStream out(&file);            
    out << text;

    return true;

}

