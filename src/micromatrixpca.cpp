#include "micromatrixpca.h"

MicroMatrixPCA::MicroMatrixPCA(Mat& mat): originalData(mat), projectedData(null)
{
    pca=PCA(originalData,Mat(),CV_PCA_DATA_AS_ROW,0);
}

MicroMatrixPCA::~MicroMatrixPCA()
{
    if(projectedData!=null)
        delete projectedData;
}

Mat MicroMatrixPCA::projectAll()
{
    if(projectedData==null)
    {
        projectedData=new Mat(originalData.rows,originalData.cols,CV_32FC1);
        for(int i=0;i<originalData.rows;i++)
            pca.project(originalData.row(i),projectedData.row(i));
    }
    return *projectedData;
}

Mat MicroMatrixPCA::backProjectAll(int columns)
{
    if(columns>originalData.cols)
        columns=originalData.cols;
    if(columns<1)
        columns=1;
    if(projectedData==null)
        projectAll();
    Mat result(originalData.rows,originalData.cols,CV_32FC1);
    for(int i=0;i<projectedData->rows;i++)
    {
        Mat row(1,projectedData->cols,CV_32FC1);
        projectedData->row(i).colRange(0,columns-1).copyTo(row);
        pca.backProject(row,result.row(i));
    }
    return result;
}
