#ifndef MICROMATRIXPCA_H
#define MICROMATRIXPCA_H

#include <opencv/cv.h>

using namespace cv;

class MicroMatrixPCA
{
private:
    PCA pca;
    Mat& originalData;
    Mat* projectedData;

public:
    MicroMatrixPCA(Mat& mat);
    ~MicroMatrixPCA();
    Mat projectAll();
    Mat backProjectAll(int columns);
};

#endif // MICROMATRIXPCA_H
