#include "micromatrixpca.h"

MicroMatrixPCA::MicroMatrixPCA(Mat& mat): originalData(mat)
{
    pca=PCA(originalData,Mat(),CV_PCA_DATA_AS_ROW,0);
}

Mat MicroMatrixPCA::projectAll()
{
    Mat pcaResult(originalData.rows,originalData.cols,CV_32FC1);
    for(int i=0;i<originalData.rows;i++)
    {
        Mat row=pcaResult.row(i);
        pca.project(originalData.row(i),row);
    }
    return pcaResult;
}
