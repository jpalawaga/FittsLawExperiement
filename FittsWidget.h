#ifndef __FITTSWIDGET_H
#define __FITTSWIDGET_H

#include <QtGui>
#include "ExperimentSettings.h"

// Forward declarations because fancy.
class QWidget;

/**
 * \class FittsWidget
 *
 * FittsWidget is the widget that will implement our experiement
 *
 * \author James Palawaga <jpalawaga@gmail.com>
 * \date March 23, 2014
 */
class FittsWidget : public QWidget {

    Q_OBJECT

    public:
        /**
         * Default Constructor
         *
         * Invokes QWidget's constructor. Sets some default values. Nothing fancy.
         *
         * @param *parent - the parent widget to attach to.
         */
        FittsWidget(QWidget *parent = 0);
        void runExperiment(ExperimentSettings e);

    protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent * e);
        void mouseMoveEvent(QMouseEvent * e);

    private:
        ExperimentSettings expSettings;
        QRect A;
        QRect B;
        int hits;
        int clicks;

};

#endif
