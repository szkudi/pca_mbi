#include "parameters.h"
#include "ui_parameters.h"

Parameters::Parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parameters)
{
    ui->setupUi(this);
}

Parameters::~Parameters()
{
    delete ui;
}

int Parameters::getStartingRow()
{
    return ui->startingRow->value();
}

int Parameters::getStartingColumn()
{
    return ui->startingColumn->value();
}

int Parameters::getEndingColumn()
{
    return ui->endingColumn->value();
}
