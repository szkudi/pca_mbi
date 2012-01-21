#include "ui_mainwindow.h"
#include <QFileDialog>
#include "mainwindow.h"
#include "aboutwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionReadFile, SIGNAL(triggered()), this, SLOT(showOpenFileDialog()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutWindow()));
    this->signalMapper = new QSignalMapper(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOpenFileDialog(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Micro Matrix (*.txt)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(Settings::getInstance().lastDir());
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
        emit openFile(fileNames.first());
    }
    Settings::getInstance().setLastDir(dialog.directory().path());
}

void MainWindow::showAboutWindow(){
    AboutWindow* win = new AboutWindow(this);
    win->show();
}

void MainWindow::updateRecentlyOpenFiles(QStringList filesNames){
    ui->menuRecentlyOpen->clear();
    foreach(QString fileName, filesNames){
        QAction* subAction = new QAction(fileName, ui->menuRecentlyOpen);
        signalMapper->setMapping(subAction, fileName);
        connect(subAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
        ui->menuRecentlyOpen->addAction(subAction);
    }
    connect(signalMapper, SIGNAL(mapped(const QString &)),this, SIGNAL(openFile(const QString)));
}
