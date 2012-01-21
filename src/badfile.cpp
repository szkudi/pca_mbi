#include "badfile.h"

BadFile::BadFile(QString msg, int line){
    this->msg = msg;
    this->line = line;
}

virtual const char* BadFile::what() const throw(){
    return this->msg.append(": line=").append(QString::number(line)).toLocal8Bit.constData();
}
