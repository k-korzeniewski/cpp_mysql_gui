#ifndef TREEMODEL_H
#define TREEMODEL_H

#include<QString>
#include<QObject>
#include<QAbstractItemModel>
#include"treeitem.h"
class TreeModel : public QAbstractItemModel
{
public:
    explicit TreeModel(const QString &data, QObject *parent = 0);
    ~TreeModel();
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                          const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
private:
    TreeItem *rootItem;
};

#endif // TREEMODEL_H
