#ifndef MICROMATRIXPCA_H
#define MICROMATRIXPCA_H

#include <opencv/cv.h>
#include <QMap>

using namespace cv;

class MicroMatrixPCA
{
private:
    PCA pca;
    Mat originalData;
    Mat* projectedData;

public:
    MicroMatrixPCA(Mat& mat);
    ~MicroMatrixPCA();
    Mat projectAll();
    Mat backProjectAll(int columns);
    QMap<int, float> calculateErrors();
};

#endif // MICROMATRIXPCA_H
