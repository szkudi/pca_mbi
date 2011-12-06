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
    DataImport di;
    QLinkedList<QSharedPointer<MicroMatrix> > results;
    foreach(QString filename, filenames){
        qDebug() << "Read file: " << filename.toLocal8Bit().constData();
        QFile file(filename);
        QSharedPointer<MicroMatrix> matrix = di.parseData(file);
        results << matrix;
    }
    qDebug() << "Import status: " << QString::number(results.size()).toLocal8Bit().constData();
}
