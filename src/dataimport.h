#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include "micromatrix.h"
#include <QIODevice>
#include <QRegExp>
#include <QSharedPointer>
#include <opencv/cv.h>

using namespace cv;

class DataImport
{
public:
    DataImport(int filesCount);
    bool parseData(QIODevice& device);
    Mat fetch();
private:
    QRegExp* headersPattern;
    QRegExp* dataPattern;

    int rowCount;
    int currentRow;
    Mat data;
};

#endif // DATAIMPORT_H
