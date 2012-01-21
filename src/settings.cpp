#include "settings.h"

const char* LAST_DIR = "state/dir";
const char* STARTING_ROW = "params/startingRow";
const char* STARTING_COLUMN = "params/startingColumn";
const char* ENDING_COLUMN = "params/endingColumn";
const char* IMPORTED_FILES = "imported/last";

Settings::Settings() :
    settings("MBI", "Micro matrix")
{
}

Settings::~Settings(){
    this->settings.sync();
}

Settings Settings::instance;

Settings& Settings::getInstance(){
    return instance;
}

QString Settings::lastDir(){
    return this->settings.value(LAST_DIR, QVariant(".")).toString();
}

void Settings::setLastDir(QString dir){
    this->settings.setValue(LAST_DIR, dir);
}

int Settings::startingRow(){
    return this->settings.value(STARTING_ROW, QVariant(1)).toInt();
}

void Settings::setStartingRow(int val){
    this->settings.setValue(STARTING_ROW, val);
}

int Settings::startingColumn(){
    return this->settings.value(STARTING_COLUMN, QVariant(1)).toInt();
}

void Settings::setStartingColumn(int val){
    this->settings.setValue(STARTING_COLUMN, val);
}

int Settings::endingColumn(){
    return this->settings.value(ENDING_COLUMN, QVariant(1)).toInt();
}

void Settings::setEndingColumn(int val){
    this->settings.setValue(ENDING_COLUMN, val);
}

QStringList Settings::lastImportedFiles(){
    return this->settings.value(IMPORTED_FILES, QVariant()).toStringList();
}

void Settings::setLastImportedFiles(QStringList filesNames){
    this->settings.setValue(IMPORTED_FILES, filesNames);
}
