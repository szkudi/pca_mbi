#ifndef IMPORTEDDATAMODEL_H
#define IMPORTEDDATAMODEL_H

#include <QAbstractTableModel>

typedef struct _ImportContext{
    QString filename;
    int rows;
    int columns;
    QVariant at(int x) const{
        switch(x){
        case 0:
            return QVariant(filename);
        case 1:
            return QVariant(rows);
        case 2:
            return QVariant(columns);
        }
        return QVariant();
    }
}ImportContext;

class ImportedDataModel: public QAbstractTableModel
{
public:
    ImportedDataModel(QObject *parent);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    //bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());

    void addImportedFile(QString name, int rows, int columns);
private:
    QList<ImportContext> dataList;
};

#endif // IMPORTEDDATAMODEL_H
