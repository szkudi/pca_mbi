#include "micromatrixpca.h"
#include <QDebug>

MicroMatrixPCA::MicroMatrixPCA(Mat& mat): projectedData(NULL)
{
    originalData=mat.t();
    qDebug()<<"PCA"<<originalData.rows<<" "<<originalData.cols;
    pca=PCA(originalData,Mat(),CV_PCA_DATA_AS_ROW,0);
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
        //for(int i=0;i<originalData.rows;i++)
        //{
            //Mat row=projectedData->row(i);
        pca.project(originalData,*projectedData);
        //}
    }
    return *projectedData;
}

Mat MicroMatrixPCA::backProjectAll(int size)
{
    if(size>projectedData->cols)
        size=projectedData->cols;
    if(size<1)
        size=1;

    if(projectedData==NULL)
        projectAll();
    Mat result(originalData.rows,originalData.cols,CV_32FC1);
    /*for(int i=0;i<projectedData->rows;i++)
    {
        Mat row=projectedData->row(i);
        qDebug()<<row.rows<<" "<<row.cols;
        qDebug()<<pca.eigenvectors.rows<<" "<<pca.eigenvectors.cols;
        qDebug()<<pca.mean.rows<<" "<<pca.mean.cols;
        Mat out=result.row(i);
        pca.backProject(row,out);
    }*/
    Mat src(projectedData->rows,projectedData->cols,CV_32FC1);
    //src.zeros();

    projectedData->copyTo(src);
    qDebug()<<size;

    if(size<src.cols)
        src.colRange(size,src.cols)=Scalar(0);

    pca.backProject(src,result);

    //qDebug()<<norm(originalData,result,CV_RELATIVE_L2);
    return result;
}

QMap<int,float> MicroMatrixPCA::calculateErrors()
{
    QMap<int,float> result;
    for(int i=1;i<=projectedData->cols;i++)
    {
        Mat backResult=backProjectAll(i);
        result.insert(i,norm(originalData,backResult,CV_RELATIVE_L2));
    }
    return result;
}
