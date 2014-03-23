#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

// Forward declarations because fancy.
class QWidget;
class FittsWidget;
class QString;

/**
 * \class MainWindow
 *
 * This is the implementation for the MainWindow that is used by the
 * texteditor. Implements various functionality on the TextEdit Widget.
 *
 * \author James Palawaga <jpalawaga@gmail.com>
 * \date Febuary 6, 2014
 */
class MainWindow : public QMainWindow {

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

