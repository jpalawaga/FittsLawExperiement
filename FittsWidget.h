#ifndef __FITTSWIDGET_H
#define __FITTSWIDGET_H

// Forward declarations because fancy.
class QMainWindow;
class QWidget;
class FittsWidget;
class QString

/**
 * \class FittsWidget
 *
 * FittsWidget is the widget that will implement our experiement
 *
 * \author James Palawaga <jpalawaga@gmail.com>
 * \date March 23, 2014
 */
class FittsWidget : public QMainWindow {

    Q_OBJECT

    public:
        /**
         * Default Constructor
         *
         * Invokes QWidget's constructor. Sets some default values. Nothing fancy.
         *
         * @param *parent - the parent widget to attach to.
         */
        MainWindow(QWidget *parent = 0);

    private:
        FittsWidget * fWid;

        /**
         * Writes a file to the disk
         *
         * Will ask before overwriting a file
         *
         * @param filename the filename/path to write to
         * @param text the contents to write to disk
         *
         * @return whether the reading/writing was successful.
         */
        bool writeFile(const QString &filename, const QString &text);

};

#endif
