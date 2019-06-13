#include "databasetreemodel.h"
#include <QSqlQuery>

DatabaseTreeModel::DatabaseTreeModel(QSqlDatabase database,QObject *parent)
    :QStandardItemModel (parent), db(database){
    this->fetch_schema();
    this->create_tree(invisibleRootItem());
}

void DatabaseTreeModel::fetch_schema(){
    QSqlQuery schema_query;
    QSqlQuery table_query;

    if(!db.isOpen())
        db.open();

    db.setDatabaseName("information_schema");
    schema_query.exec("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA");

    // TODO: Try to split for two NOT NESTED loops.
    while(schema_query.next()){
        QString schema = schema_query.value(0).toString();
        table_query.exec("SELECT table_name FROM information_schema.tables where table_schema='"+schema+"';");

        QVector<QString> tables;

        while(table_query.next()){
            QString table = table_query.value(0).toString();
            tables.push_back(table);
        }
        schema_table_map.insert(schema,tables);
    }
}

void DatabaseTreeModel::create_tree(QStandardItem* root){
    for(QString key : schema_table_map.keys()){
        QStandardItem* schema_item(new QStandardItem);
        schema_item->setText(key);
        for(QString value: schema_table_map.value(key)){
            QStandardItem* table(new QStandardItem);
            table->setText(value);
            schema_item->appendRow(table);
        }
        root->appendRow(schema_item);
    }
}


