#include <QtCore/QCoreApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc){
        std::cout << "Użycie: \n" << argv[0] << "<filename> <begin> <end> " << std::endl;
    }
    char * outputFilenam = argv[1];
    return a.exec();
}
