#include "parameters.h"
#include "ui_parameters.h"
#include "settings.h"

Parameters::Parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parameters)
{
    ui->setupUi(this);
    Settings& settings = Settings::getInstance();
    ui->startingColumn->setValue(settings.startingColumn());
    ui->startingRow->setValue(settings.startingRow());
    ui->endingColumn->setValue(settings.endingColumn());
}

Parameters::~Parameters()
{
    Settings& settings = Settings::getInstance();
    settings.setStartingRow(getStartingRow());
    settings.setStartingColumn(getStartingColumn());
    settings.setEndingColumn(getEndingColumn());
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
