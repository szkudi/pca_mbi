#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <QIODevice>
#include <QRegExp>
#include <QSharedPointer>
#include <opencv/cv.h>

using namespace cv;

class DataImport
{
public:
    DataImport(int startAtLine, int firstColumn, int lastColumn);
    Mat parseData(QIODevice& device);
private:
    //QRegExp* headersPattern;
    QRegExp* dataPattern;

    int startAtLine;
    int firstColumn;
    int lastColumn;
};

#endif // DATAIMPORT_H
