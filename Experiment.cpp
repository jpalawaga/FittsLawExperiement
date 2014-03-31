#include <unistd.h>
#include <QtGui>
#include <QSqlQuery>
#include <QSqlError>
#include "Experiment.h"
#include "Test.h"
#include <cmath>

Experiment::Experiment(FittsWidget * fw, QSqlDatabase database) {
    db = database;
    widget = fw;
    experimentNumber = 0;
    numberOfTrainingRounds = 0;
    volunteerId = 0;
    aVal = 0;
    bVal = 0;
    coeff = 0;
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
    if (experimentNumber > 0) {
        if (db.open()) {
            QSqlQuery query(db);
            QString q = QString("INSERT INTO testAccuracy VALUES(%1, %2, %3)").arg(volunteerId).arg(experimentNumber-1).arg(tests[experimentNumber].getAccuracy());
            query.exec(q);
            // @TODO Proper error handling
            //qDebug() << q;
            //QSqlError e = query.lastError();
            //qDebug() << e.text();
            query.clear();
        }
    }
        
        if (experimentNumber == numberOfTrainingRounds) {
        calculateValues();
        if (db.open()) {
            QSqlQuery query(db);
            QString q = QString("UPDATE volunteers SET a=%1, b=%2, coeff=%3 WHERE id=%4").arg(aVal).arg(bVal).arg(coeff).arg(volunteerId);
            query.exec(q);
            // @TODO Proper error handling
            //qDebug() << q;
            //QSqlError e = query.lastError();
            //qDebug() << e.text();
            query.clear();
        }
    }

    if (experimentNumber < tests.size()) {
        ExperimentSettings es = tests[experimentNumber].getSettings();
        widget->runExperiment(es);
        
        if (experimentNumber >= numberOfTrainingRounds) {
            int metronomeSpeed = (int)(60000 / timeCalc(es.getDistance(), es.getSize())); 
            QMessageBox::information(0, "Metronome Speed", QString("Set metronome to %1 bps").arg(metronomeSpeed));
        }
         
        experimentNumber++;
    } else {
        QMessageBox::information(this, tr("Done"), tr("Testing is complete."));
    }
}

void Experiment::calculateValues() {
    Test test;
    int j = 0;
     
    double sumx = 0;
     double sumy = 0;
     double sumXxY = 0;
     double sumX2 = 0;
     double sumY2 = 0;  
     int n = 0;  // Initialize variables for use in the following calculation 
     
     for (; j < numberOfTrainingRounds; j++) {
         test = tests[j];
         for(int i = 1 ; i < test.clicks.size(); i++) {
             // NOTE: Omitted from this calculation: First click (0ms) and clicks following a miss.
             if ((!test.clicks[i].hit) || (!test.clicks[i-1].hit)) {
                continue;
             }

             double D = test.getSettings().getDistance();
             double W = test.getSettings().getSize();
             int T = test.clicks[i].time;
             double x = calculateX(D,W);
             double y = static_cast<double>(T);
             
             sumx += x;
             sumy += y;
             sumXxY += (x*y);
             sumX2 += (x*x);
             sumY2 += (y*y);
             n++;
          }   
        } 
      qDebug() << n << " user hits used to calc A and B." << endl;
      
      // Does the regression calculation to find user's average a and b coefficients 
      bVal = ( (n*sumXxY) - (sumx*sumy) ) / ( (n*sumX2)- (sumx*sumx) );
      aVal = ( sumy - (bVal*sumx) ) / n;
      coeff = (n * sumXxY - sumx * sumy) / sqrt(  (n * sumX2 - sumx * sumx) * (n * sumY2 - sumy * sumy) );
         
          qDebug() << "sumx: " << sumx << " sumy: " << sumy << " sumXxY: " << sumXxY;
          qDebug() << "Top A: "<< n * sumXxY << " // Top B: " << sumx * sumy << endl;
          
          qDebug() << "A: " << aVal << " B: " << bVal << " Coeff: " << coeff;
}

double Experiment::timeCalc(double D, double W) {
   return (aVal + (bVal * ( calculateX(D, W) ) ) );
}

// Helper function to isolate the calculation of x based on D and W for
// linear regression 
double Experiment::calculateX(double D, double W){
    return log2( 1.0 + ( (D) / W) );
}

void Experiment::addTestTrial(ExperimentSettings s) {
    Test t(s);
    tests.push_back(t);
}

void Experiment::addTrainingTrial(ExperimentSettings s) {
    Test t(s);
    tests.insert(numberOfTrainingRounds, s);
    numberOfTrainingRounds++;
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
