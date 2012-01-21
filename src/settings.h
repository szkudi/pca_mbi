#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>

class Settings
{
public:
    static Settings& getInstance();
    virtual ~Settings();

    QString lastDir();
    void setLastDir(QString dir);
    QStringList lastImportedFiles();
    void setLastImportedFiles(QStringList filesNames);

    int startingRow();
    void setStartingRow(int val);
    int startingColumn();
    void setStartingColumn(int val);
    int endingColumn();
    void setEndingColumn(int val);
private:
    explicit Settings();

    QSettings settings;
    static Settings instance;
};

#endif // SETTINGS_H
