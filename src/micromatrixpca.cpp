#include "micromatrixpca.h"
#include <QDebug>

MicroMatrixPCA::MicroMatrixPCA(Mat& mat): originalData(mat), projectedData(NULL)
{
    pca=PCA(originalData,Mat(),CV_PCA_DATA_AS_COL,0);
}

MicroMatrixPCA::~MicroMatrixPCA()
{
    if(projectedData!=NULL)
        delete projectedData;
}

Mat MicroMatrixPCA::projectAll()
{
    if(projectedData==NULL)
    {
        projectedData=new Mat(originalData.rows,originalData.cols,CV_32FC1);
        for(int i=0;i<originalData.cols;i++)
        {
            Mat row=projectedData->col(i);
            pca.project(originalData.col(i),row);
        }
    }
    return *projectedData;
}

Mat MicroMatrixPCA::backProjectAll(int size)
{
    if(size>projectedData->rows)
        size=projectedData->rows;
    if(size<1)
        size=1;
    if(projectedData==NULL)
        projectAll();
    Mat result(originalData.rows,originalData.cols,CV_32FC1);
    for(int i=0;i<projectedData->cols;i++)
    {
        Mat col(size,1,CV_32FC1);
        projectedData->col(i).copyTo(col);
        result.col(i)=pca.backProject(col);
    }
    return result;
}
