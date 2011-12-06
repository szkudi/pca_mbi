#ifndef MICROMATRIX_H
#define MICROMATRIX_H

#include <QString>
#include <QLinkedList>

class MicroMatrix
{
public:
    MicroMatrix();

    void addHeader(QString name, QString value);
    void setColumnNames(QLinkedList<QString> columns);
    void setColumnValues(QLinkedList<QString> values);
};

#endif // MICROMATRIX_H
