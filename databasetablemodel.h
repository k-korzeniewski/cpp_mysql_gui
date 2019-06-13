#ifndef DATABASETABLEMODEL_H
#define DATABASETABLEMODEL_H

#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMatrix>
class DatabaseTableModel : public QStandardItemModel
{
public:
    DatabaseTableModel(QSqlDatabase database,QString schema,QString table, QObject* = nullptr);
    void save_table();
private:
    QSqlDatabase db;
    QString table;
    QString schema;
    QVector<QString> column_names_vector;
    QList<QList<QStandardItem*>> fields;
    void fetch_column_names();
    void render_column_names();
    void fetch_rows();
    void render_rows();
    void save_row(QList<QStandardItem*> row);
    QString prepare_query();
    QString prepare_update_query(QList<QStandardItem*>);
};

#endif // DATABASETABLEMODEL_H
