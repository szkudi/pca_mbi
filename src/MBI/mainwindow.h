#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    void openFile(QStringList filenames);

private slots:
    void showOpenFileDialog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
