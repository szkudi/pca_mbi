#ifndef MICROMATRIXPCA_H
#define MICROMATRIXPCA_H

#include <opencv/cv.h>

using namespace cv;

class MicroMatrixPCA
{
private:
    PCA pca;
    Mat& originalData;

public:
    MicroMatrixPCA(Mat& mat);
    Mat projectAll();
};

#endif // MICROMATRIXPCA_H
