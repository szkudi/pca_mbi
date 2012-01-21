#include <QFile>
#include <QDebug>
#include "controller.h"
#include "mainwindow.h"
#include "dataimport.h"
#include "parameters.h"

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
    Parameters params;
    if(params.exec()==true)
    {
        qDebug() << "Starting row:" << params.getStartingRow();
        qDebug() << "Starting column:" << params.getStartingColumn();
        qDebug() << "Ending column:" << params.getEndingColumn();
        QString errorIn;
        foreach(QString filename, filenames){
            qDebug() << "Read file: " << filename.toLocal8Bit().constData();
            QFile file(filename);
            DataImport di(params.getStartingRow() - 1, params.getStartingColumn() - 1, params.getEndingColumn() - 1);
            Mat pcaInputData = di.parseData(file);
            bool success = pcaInputData.rows > 0;
            if(!success){
                errorIn = filename;
                qDebug() << "Error in: " << errorIn;
                break;
            }
            qDebug() << "Import status: " << success;
        }
    }
}
