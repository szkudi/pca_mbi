#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include "mainwindow.h"
#include "importeddatamodel.h"
#include "cv.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(MainWindow* parent );
    void init();

private slots:
    void openFile(QString filename);
    void saveMat(const char* filename, cv::Mat mat);

signals:
    void recentlyImportedFilesChanged(QStringList listOfFilesNames);

private:
    void addFileToRecentlyOpen(QString fileName);

    MainWindow *view;
    ImportedDataModel *importedDataModel;
};

#endif // CONTROLLER_H
