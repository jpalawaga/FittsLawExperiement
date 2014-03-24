#include <QtGui>
#include "FittsWidget.h"

FittsWidget::FittsWidget(QWidget *p) {
    setMouseTracking(true);
    update();
}

void FittsWidget::runExperiment(ExperimentSettings e) {
    expSettings = e;
    QDesktopWidget widget;
    QRect scrSize = widget.availableGeometry(widget.primaryScreen());
    A = QRect(scrSize.width() /2 - e.getDistance()/2, scrSize.height() /2, e.getSize(), 40);
    B = QRect(scrSize.width() /2 + e.getDistance()/2, scrSize.height() /2, e.getSize(), 40);
    hits = 0;
    clicks = 0;
    update();
}

void FittsWidget::paintEvent(QPaintEvent * event) {
    QPainter p(this);
    p.setBrush(QBrush(Qt::black));
    p.drawRect(A);
    p.drawRect(B);
}

void FittsWidget::mousePressEvent(QMouseEvent * e) {
    bool hit = false;
    clicks++;

    if (A.contains(e->pos()) || B.contains(e->pos())) {
        qDebug() << "HIT";
        hit = true;
        hits++;
    }

    emit buttonClicked (e->pos(), 0, hit);
    
    if (expSettings.getMethod() == ExperimentSettings::BYCLICKS) {
        if (clicks >= expSettings.getMax()) {
            emit experimentComplete();
        }
    }

    if (expSettings.getMethod() == ExperimentSettings::BYHITS) {
        if (hits >= expSettings.getMax()) {
            emit experimentComplete();
            qDebug() << "HITi";
        }
    }
}

