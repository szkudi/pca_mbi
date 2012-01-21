#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>

class Settings
{
public:
    static Settings& getInstance();

    QString lastDir();
    void setLastDir(QString dir);
    int startingRow();
    void setStartingRow(int val);
    int startingColumn();
    void setStartingColumn(int val);
    int endingColumn();
    void setEndingColumn(int val);
private:
    explicit Settings(QObject *parent = 0);

    QSettings settings;
    static Settings instance;
};

#endif // SETTINGS_H
