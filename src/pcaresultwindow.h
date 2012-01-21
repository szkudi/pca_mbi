#ifndef PCARESULTWINDOW_H
#define PCARESULTWINDOW_H

#include <QDialog>
#include <QMap>

namespace Ui {
    class PCAResultWindow;
}

class PCAResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PCAResultWindow(QWidget *parent, QMap<int, float> pcaErrorPerFeaturesCount);
    ~PCAResultWindow();

private:
    Ui::PCAResultWindow *ui;
};

#endif // PCARESULTWINDOW_H
