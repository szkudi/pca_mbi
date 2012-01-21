#include "dataimport.h"

#include <QStringList>
#include <QDebug>
#include <iostream>

DataImport::DataImport()
{
    this->headersPattern = new QRegExp("!([^=]+)=(.*)");
    this->dataPattern  = new QRegExp("([^\t]*)[\t]");
}

enum FilePart{
    HEADERS,
    COLUMNS,
    DATA
};

QSharedPointer<MicroMatrix> DataImport::parseData(QIODevice& device){
    std::cout << "Start import..." << std::endl;
    if (!device.open(QIODevice::ReadOnly)){
        std::cout << "Cannot open" << std::endl;
        return QSharedPointer<MicroMatrix>(NULL);
    }
    char buf[4096];
    MicroMatrix* result = new MicroMatrix();
    FilePart current = HEADERS;
    try{
        while(true){
            qint64 lineLength = device.readLine(buf, sizeof(buf));
            if (lineLength != -1) {
                if(this->headersPattern->exactMatch(buf)){
                    QStringList groups = this->headersPattern->capturedTexts();
                    result->addHeader(groups.at(1), groups.at(2));

                }else {
                    if(current == HEADERS){
                        current = COLUMNS;
                    }else if(current == COLUMNS){
                        current = DATA;
                    }
                    int pos = 0;

                    QLinkedList<QString> columnValues;
                    while ((pos = this->dataPattern->indexIn(buf, pos)) != -1) {
                        pos += this->dataPattern->matchedLength();
                        columnValues << this->dataPattern->cap(1);
                    }

                    if(current == COLUMNS){
                        result->setColumnNames(columnValues);
                    }else{
                        result->setColumnValues(columnValues);
                    }
                }
            }else{
                break;
            }
        }
        return QSharedPointer<MicroMatrix>(result);
    }catch(...){
        delete result;
        return QSharedPointer<MicroMatrix>(NULL);
    }
}
