#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include "micromatrix.h"
#include <QIODevice>
#include <QRegExp>
#include <QSharedPointer>

class DataImport
{
public:
    DataImport();

    QSharedPointer<MicroMatrix> parseData(QIODevice& device);

private:
    QRegExp* headersPattern;
    QRegExp* dataPattern;
};

#endif // DATAIMPORT_H
