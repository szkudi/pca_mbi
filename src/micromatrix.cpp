#include "micromatrix.h"
#include <QString>
#include <QDebug>

MicroMatrix::MicroMatrix()
{
}

void MicroMatrix::addHeader(QString name, QString value){
    qDebug() << "H: " << name.toLocal8Bit().constData() << " -> " << value.toLocal8Bit().constData() << "\n";
}

void MicroMatrix::setColumnNames(QLinkedList<QString> columns){
    qDebug() << "Columns: ";
    foreach (const QString &str, columns){
        qDebug() << str << "\n";
    }
}

void MicroMatrix::setColumnValues(QLinkedList<QString> value){
    //qDebug() << "Values: ";
    //foreach (const QString &str, columns){
    //    qDebug() << str << "\n";
    //}
}
