#include <QFile>
#include <QDebug>
#include "controller.h"
#include "mainwindow.h"
#include "dataimport.h"
#include "parameters.h"
#include "pcaresultwindow.h"
#include "micromatrixpca.h"
#include "settings.h"

#include <fstream>
#include <iostream>

const int RECENTLY_OPEN_MAX = 10;

Controller::Controller(MainWindow *parent) :
    QObject(parent)
{
    view = parent;
}

void Controller::init(){
    connect(view, SIGNAL(openFile(QString)), this, SLOT(openFile(QString)));
    connect(this, SIGNAL(recentlyImportedFilesChanged(QStringList)), view, SLOT(updateRecentlyOpenFiles(QStringList)));
    QStringList recentlyOpen = Settings::getInstance().lastImportedFiles();
    view->updateRecentlyOpenFiles(recentlyOpen);
    view->show();
}

void Controller::openFile(QString filename){
    Parameters params;
    if(params.exec()==true)
    {
        qDebug() << "Starting row:" << params.getStartingRow();
        qDebug() << "Starting column:" << params.getStartingColumn();
        qDebug() << "Ending column:" << params.getEndingColumn();
        qDebug() << "Read file: " << filename.toLocal8Bit().constData();
        this->addFileToRecentlyOpen(filename);
        QFile file(filename);
        DataImport di(params.getStartingRow() - 1, params.getStartingColumn() - 1, params.getEndingColumn() - 1);
        Mat pcaInputData = di.parseData(file);
        bool success = pcaInputData.rows > 0;
        if(!success){
            qDebug() << "Error in: " << filename;
            return;
        }
        qDebug() << "Import status: " << success;
        MicroMatrixPCA pca(pcaInputData);
        Mat pca_pro = pca.projectAll();
        saveMat("pca.txt", pca_pro);
        Mat pca_backpro = pca.backProjectAll(100);
        saveMat("pca_back.txt", pca_backpro);
        QMap<int, float> map=pca.calculateErrors();
        PCAResultWindow *errorWindow = new PCAResultWindow(NULL, map);
        errorWindow->show();

    }
}

void Controller::addFileToRecentlyOpen(QString fileName){
    QStringList recentlyOpen = Settings::getInstance().lastImportedFiles();
    bool editedList = false;
    if(!recentlyOpen.contains(fileName)){
        recentlyOpen.prepend(fileName);
        editedList = true;
    }
    while(true){
        if(recentlyOpen.size() > RECENTLY_OPEN_MAX){
            recentlyOpen.takeLast();
            editedList = true;
        }else{
            break;
        }
    }
    if(editedList){
        emit recentlyImportedFilesChanged(recentlyOpen);
        Settings::getInstance().setLastImportedFiles(recentlyOpen);
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
