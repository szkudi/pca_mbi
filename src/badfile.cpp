#include "badfile.h"

BadFile::BadFile(QString msg, int line){
    this->msg = msg;
    this->line = line;
    QString lineStr = QString::number(line);
    QString prefix(": line=");
    msg.append(prefix);
    msg.append(lineStr);
}

BadFile::~BadFile() throw(){
}

const char* BadFile::what() const throw(){
   return msg.toLocal8Bit().constData();
}
