#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include "mainwindow.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(MainWindow* parent );
    void init();

signals:

public slots:

private slots:
    void openFile(QStringList filename);
private:
    MainWindow *view;
};

#endif // CONTROLLER_H
