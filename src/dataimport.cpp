#include "dataimport.h"

#include <QStringList>
#include <QDebug>
#include <iostream>

DataImport::DataImport(int startAtLine, int firstColumn, int lastColumn)
{
    //this->headersPattern = new QRegExp("!([^=]+)=(.*)");
    this->dataPattern  = new QRegExp("([^\t]*)[\t]");

    this->startAtLine = startAtLine;
    this->firstColumn = firstColumn;
    this->lastColumn = lastColumn;
}

Mat DataImport::parseData(QIODevice& device){
    std::cout << "Start import..." << std::endl;
    int currentCol = 0;
    int currentLine = -1;
    int currentRow = 0;
    int lineCount = 0;
    if (!device.open(QIODevice::ReadOnly)){
        std::cout << "Cannot open" << std::endl;
        return Mat();
    }
    char buf[4096];

    std::cout << "Counting file lines" << std::endl;
    while(device.readLine(buf, sizeof(buf)) != -1){
        lineCount++;
    }
    std::cout << "File lines " << lineCount << std::endl;
    device.seek(0);
    Mat output;
    try{
        while(true){
            qint64 lineLength = device.readLine(buf, sizeof(buf));
            if (lineLength != -1) {
                currentLine ++;
                if(currentLine < this->startAtLine){
                    //ignore first lines
                    continue;
                }

                int pos = 0;

                QVector<QString> columnValues;
                while ((pos = this->dataPattern->indexIn(buf, pos)) != -1) {
                    pos += this->dataPattern->matchedLength();
                    columnValues << this->dataPattern->cap(1);
                }

                std::cout << "Line " << currentLine << std::endl;

                if(output.rows == 0){
                    //create output matrix
                    int rowCount = lineCount - startAtLine;
                    output = Mat(rowCount, columnValues.size(), CV_32F);
                }
                currentCol = 0;
                for(int x=this->firstColumn ; x <= lastColumn ; x++){
                    QString strValue = columnValues[x];
                    float value = strValue.toFloat();
                    output.at<float>(currentRow, currentCol) = value;
                    currentCol++;
                }
                currentRow ++;
            }else{
                break;
            }
        }
        return output;
    }catch(...){
        return Mat();
    }
}
