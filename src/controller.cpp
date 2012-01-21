#include <QFile>
#include <QDebug>
#include "controller.h"
#include "mainwindow.h"
#include "dataimport.h"

Controller::Controller(MainWindow *parent) :
    QObject(parent)
{
    view = parent;
}

void Controller::init(){
    connect(view, SIGNAL(openFile(QStringList)), this, SLOT(openFile(QStringList)));
    view->show();
}

void Controller::openFile(QStringList filenames){
    DataImport di(filenames.size());
    bool success;
    QString errorIn;
    foreach(QString filename, filenames){
        qDebug() << "Read file: " << filename.toLocal8Bit().constData();
        QFile file(filename);
        bool success = di.parseData(file);
        if(!success){
            errorIn = filename;
            qDebug() << "Error in: " << errorIn;
            break;
        }
    }
    Mat pcaInputData = di.fetch();
    qDebug() << "Import status: " << success;

}
