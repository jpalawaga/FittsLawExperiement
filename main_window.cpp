// Name:  James Palawaga
//  SN:    001158466
//    
//  MainWindow implementation for Part 3 of the assignment.

#include "main_window.h"
#include <QtGui>
#include "FittsWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

     setCentralWidget(fWid = new FittsWidget(parent));

     connect (textEdit, SIGNAL(textChanged()), this, SLOT(setTextModified()));
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

