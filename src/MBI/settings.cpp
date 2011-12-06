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
