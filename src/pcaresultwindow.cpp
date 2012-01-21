#include "pcaresultwindow.h"
#include "ui_pcaresultwindow.h"

PCAResultWindow::PCAResultWindow(QWidget *parent, QMap<int, float> pcaErrorPerFeatures) :
    QDialog(parent),
    ui(new Ui::PCAResultWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(pcaErrorPerFeatures.count());
    ui->tableWidget->setColumnCount(2);
    QStringList headers;
    headers << "Features count";
    headers << "Error";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    QList<int> keys = pcaErrorPerFeatures.keys();
    int rowCounter = 0;
    foreach(int key, keys){
        float pcaError = pcaErrorPerFeatures[key];
        ui->tableWidget->setItem(rowCounter, 0, new QTableWidgetItem(QString::number(key)));
        ui->tableWidget->setItem(rowCounter, 1, new QTableWidgetItem(QString::number(pcaError)));
        rowCounter++;
    }
}

PCAResultWindow::~PCAResultWindow()
{
    delete ui;
}
