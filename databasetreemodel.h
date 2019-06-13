#ifndef DATABASETREEMODEL_H
#define DATABASETREEMODEL_H

#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QMap>
#include <QDebug>
class DatabaseTreeModel : public QStandardItemModel
{
public:
    DatabaseTreeModel(QSqlDatabase,QObject * = nullptr);
    void fetch_schema();
    void create_tree(QStandardItem*);
private:
    QSqlDatabase db;
    QMap<QString, QVector<QString>> schema_table_map;

};

#endif // DATABASETREEMODEL_H
