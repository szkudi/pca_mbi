#include "importeddatamodel.h"
#include <QDebug>

ImportedDataModel::ImportedDataModel(QObject *parent): QAbstractTableModel(parent)
{    
}

int ImportedDataModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return this->dataList.size();
}

int ImportedDataModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 3;
}

QVariant ImportedDataModel::data(const QModelIndex &index, int role) const{
    const int rowIdx = index.row();
    const int colIdx = index.column();
    const ImportContext d = this->dataList.at(rowIdx);
    switch(role){
    case Qt::DisplayRole:
        return d.at(colIdx);
        break;    
    }
    return QVariant();
}

QVariant ImportedDataModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Plik");
            case 1:
                return QString("Wierszy");
            case 2:
                return QString("Kolumn");
            }
        }
    }
    return QVariant();
}

void ImportedDataModel::addImportedFile(QString name, int rows, int columns){
    int position = this->dataList.size();
    beginInsertRows(QModelIndex(), position, position);
    ImportContext ctx;
    ctx.filename = name;
    ctx.rows = rows;
    ctx.columns = columns;
    dataList.append(ctx);
    endInsertRows();
    emit dataChanged(createIndex(position, 0), createIndex(position, 2));
}
