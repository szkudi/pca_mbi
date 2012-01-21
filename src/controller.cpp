#include <QFile>
#include <QDebug>
#include "controller.h"
#include "mainwindow.h"
#include "dataimport.h"
#include "parameters.h"
#include "pcaresultwindow.h"
#include "micromatrixpca.h"

#include <fstream>
#include <iostream>

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
            MicroMatrixPCA pca(pcaInputData);
            Mat pca_pro = pca.projectAll();
            saveMat("pca.txt", pca_pro);
            Mat pca_backpro = pca.backProjectAll(10);
            saveMat("pca_back.txt", pca_backpro);
            QMap<int, float> map;
            map[1] = 0.01;
            map[3] = 0.02;
            map[4] = 0.03;
            PCAResultWindow *errorWindow = new PCAResultWindow(NULL, map);
            errorWindow->show();
        }
    }
}


void Controller::saveMat(char* filename, cv::Mat mat){
    std::fstream out;

    out.open(filename, std::fstream::out);

    for(int i = 0; i < mat.rows; ++i){
        for(int j = 0; j < mat.cols; ++j){
            out <<  mat.at<float>(i, j) << "\t";
        }
        out << std::endl;
    }

    out.close();
}
