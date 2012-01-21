#include "settings.h"

Settings::Settings(QObject *parent) :
    settings("MBI", "Micro matrix")
{
}

Settings Settings::instance;

Settings& Settings::getInstance(){
    return instance;
}

QString Settings::lastDir(){
    return this->settings.value("state/dir", QVariant(".")).toString();
}

void Settings::setLastDir(QString dir){
    this->settings.setValue("state/dir", dir);
}

int Settings::startingRow(){
    return this->settings.value("params/startingRow", QVariant(1)).toInt();
}

void Settings::setStartingRow(int val){
    this->settings.setValue("params/startingRow", val);
}

int Settings::startingColumn(){
    return this->settings.value("params/startingColumn", QVariant(1)).toInt();
}

void Settings::setStartingColumn(int val){
    this->settings.setValue("params/startingColumn", val);
}

int Settings::endingColumn(){
    return this->settings.value("params/endingColumn", QVariant(1)).toInt();
}

void Settings::setEndingColumn(int val){
    this->settings.setValue("params/endingColumn", val);
}
