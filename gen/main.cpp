#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <cstdlib>

class Point{
public:
    Point();
    Point(int x, int y, int z);

    int x;
    int y;
    int z;

    friend std::ostream& operator<< (std::ostream&, const Point&);
};

Point::Point(){ x = 0; y = 0; z = 0;}
Point::Point(int x, int y, int z){this->x = x; this->y = y; this->z = z;}

std::ostream& operator<< (std::ostream& output, const Point& P){
    output << P.x << " " << P.y << " " << P.z;

    return output;
}

int main(int argc, char *argv[])
{
    Point start, end;
    Point *cameras;
    int cameras_num;
    int measures_cnt;

    QCoreApplication a(argc, argv);

//    std::cout << argc;

    if(argc < 9){
        std::cout << "Użycie: \n" << argv[0] << "<out_filename> <begin_x> <begin_y ><begin_z> <end_x> <end_y> <end_z> <camera_num> [<camera_x> <camera_y>] <measures_cnt>" << std::endl;
        return -1;
    }

    int idx = 1;
    char * outputFilename = argv[idx++];

    start.x = std::atoi(argv[idx++]);
    start.y = std::atoi(argv[idx++]);
    start.z = std::atoi(argv[idx++]);

//    std::cout << start << std::endl;

    end.x = std::atoi(argv[idx++]);
    end.y = std::atoi(argv[idx++]);
    end.z = std::atoi(argv[idx++]);

//    std::cout << end << std::endl;

    cameras_num = std::atoi(argv[idx++]);
    cameras = new Point[cameras_num];

    for(int i = 0; i < cameras_num; ++i){
        cameras[i].x = std::atoi(argv[idx++]);
        cameras[i].y = std::atoi(argv[idx++]);

//        std::cout << cameras[i] << std::endl;
    }

    measures_cnt = std::atoi(argv[idx++]);

    std::fstream output;
    output.open (outputFilename, std::fstream::out);

    double x_chng = (double)(end.x - start.x)/measures_cnt;
    double y_chng = (double)(end.y - start.y)/measures_cnt;
    double z_chng = (double)(end.z - start.z)/measures_cnt;
//    std::cout << z_chng << std::endl;

    for(int i = 0; i < cameras_num; ++i){
        for(int j = 0; j < measures_cnt; ++j){
            if(j != 0)
                output << "\t";
            output << (double)start.x + j * x_chng - (double)cameras[i].x;
        }
        output << "\t" << std::endl;
        for(int j = 0; j < measures_cnt; ++j){
            if(j != 0)
                output << "\t";
            output << (double)start.y + j * y_chng - (double)cameras[i].y;
        }
        output << "\t" << std::endl;

        for(int j = 0; j < measures_cnt; ++j){
            if(j != 0)
                output << "\t";
            output << (double)start.z + j * z_chng;
        }
        output << "\t" << std::endl;

    }

//    for(int i = 0; i < measures_cnt; ++i){
//      for(int j = 0; j < cameras_num; ++j){
//            output << (double)start.x + i * x_chng - (double)cameras[j].x << "\t" << (double)start.y + i * y_chng - (double)cameras[j].y << "\t" << (double)start.z + i * z_chng << "\t";
//        }
//        output << std::endl;
//    }

   output.close();

    return 0;
}
