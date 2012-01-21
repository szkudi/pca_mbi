#include "ui_mainwindow.h"
#include <QFileDialog>
#include "mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionReadFile, SIGNAL(triggered()), this, SLOT(showOpenFileDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOpenFileDialog(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Micro Matrix (*.xls *.xls.gz)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(Settings::getInstance().lastDir());
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
        emit openFile(fileNames);
    }
    Settings::getInstance().setLastDir(dialog.directory().path());
}
