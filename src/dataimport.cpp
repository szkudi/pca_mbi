#include "dataimport.h"

#include <QStringList>
#include <QDebug>
#include <iostream>

const int columnOfIntrests = 3;

DataImport::DataImport(int filecount)
{
    this->headersPattern = new QRegExp("!([^=]+)=(.*)");
    this->dataPattern  = new QRegExp("([^\t]*)[\t]");
    this->rowCount = filecount;
    this->currentRow = -1;
}

enum FilePart{
    HEADERS,
    COLUMNS,
    DATA
};

bool DataImport::parseData(QIODevice& device){
    std::cout << "Start import..." << std::endl;
    this->currentRow ++;
    int currentCol = 0;
    if (!device.open(QIODevice::ReadOnly)){
        std::cout << "Cannot open" << std::endl;
        return false;
    }
    char buf[4096];
    FilePart current = HEADERS;
    try{
        while(true){
            qint64 lineLength = device.readLine(buf, sizeof(buf));
            if (lineLength != -1) {
                if(this->headersPattern->exactMatch(buf)){
                    //QStringList groups = this->headersPattern->capturedTexts();
                    //result->addHeader(groups.at(1), groups.at(2));

                }else {
                    if(current == HEADERS){
                        current = COLUMNS;
                    }else if(current == COLUMNS){
                        current = DATA;
                    }
                    int pos = 0;

                    QVector<QString> columnValues;
                    while ((pos = this->dataPattern->indexIn(buf, pos)) != -1) {
                        pos += this->dataPattern->matchedLength();
                        columnValues << this->dataPattern->cap(1);
                    }

                    if(this->data.rows == 0){
                        //create output matrix
                        this->data = Mat(this->rowCount, columnValues.size(), 0);
                    }

                    if(current == COLUMNS){
                        //ignore
                    }else{
                        //result->setColumnValues(columnValues);
                        assert(columnValues.size() < columnOfIntrests);
                        QString strValue = columnValues[columnOfIntrests];
                        int value = strValue.toInt();
                        this->data.at<int>(this->currentRow, currentCol) = value;
                        currentCol++;
                    }
                }
            }else{
                break;
            }
        }
        return true;
    }catch(...){
        return false;
    }
}

Mat DataImport::fetch(){
    return data;
}
