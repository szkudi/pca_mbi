#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSignalMapper>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void openFile(QString filename);

public slots:
    void updateRecentlyOpenFiles(QStringList filesNames);

private slots:
    void showOpenFileDialog();
    void showAboutWindow();

private:
    Ui::MainWindow *ui;
    QSignalMapper *signalMapper;
};

#endif // MAINWINDOW_H
