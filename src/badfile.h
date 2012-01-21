#ifndef BADFILE_H
#define BADFILE_H

#include <QString>

using namespace std;

class BadFile: public exception
{
public:
    BadFile(QString msg, int line);
    virtual const char* what() const throw();
    virtual ~BadFile() throw();
private:
    QString msg;
    int line;
};

#endif // BADFILE_H
