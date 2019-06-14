#include "databasetablemodel.h"
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidgetItem>
DatabaseTableModel::DatabaseTableModel(QSqlDatabase database, QString schema,QString table, QObject *parent)
    :QStandardItemModel (parent),db(database), table(table), schema(schema)
{
    this ->fetch_column_names();
    this ->render_column_names();
    this ->fetch_rows();
    this ->render_rows();
}

void DatabaseTableModel::fetch_column_names(){
    if(!db.open())
        db.open();

    QSqlQuery query;
    query.exec("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = '"
               +schema+"' AND TABLE_NAME = '"+table+"';");
    while(query.next()){
        QString column_name = query.value(0).toString();
        this->column_names_vector.push_back(column_name);
    }
}

void DatabaseTableModel::render_column_names(){
    for(int i = 0; i < column_names_vector.size(); i++){
        QStandardItem* header = new QStandardItem;
        header->setText(QString(column_names_vector[i]));
        this->setHorizontalHeaderItem(i,header);
    }
}

void DatabaseTableModel::fetch_rows(){
    if(!db.open())
        db.open();
    QSqlQuery query;
    db.setDatabaseName(schema);
    query.exec("SELECT * FROM "+table);
    while(query.next()){
        QList<QStandardItem*> row;
        for(int i = 0; i<columnCount(); i++){
            QStandardItem *item = new QStandardItem;
            item->setText(query.value(i).toString());
            row.push_back(item);
        }
        fields.push_back(row);
    }
}

void DatabaseTableModel::render_rows(){
    for(int i = 0; i < fields.size(); i++){
        qDebug() << fields.size() << endl;
           this->appendRow(fields[i]);
    }
}

void DatabaseTableModel::save_table(){
    qDebug() << fields.size() << "rows" << endl;
    for(int i = 0; i < fields.size(); i++){
        save_row(fields.at(i));
    }
}

QString DatabaseTableModel::prepare_query(){
    QString query_string ="INSERT INTO "+table+" (";
    for(int col = 0; col < column_names_vector.size(); col++){
        query_string+=column_names_vector.at(col);
        if(col != column_names_vector.size() - 1)
            query_string+=",";
    }
    query_string+=") VALUES (";
    for(int col = 0; col < column_names_vector.size(); col++){
        query_string+='?';
        if(col != column_names_vector.size() - 1)
            query_string+=",";
    }
    query_string+=")";

    return query_string;
}

QString DatabaseTableModel::prepare_update_query(QList<QStandardItem*> row){
    QString query_string = "REPLACE INTO "+schema+"."+ table + " ( ";
    for(int col = 0; col < column_names_vector.size(); col++){
            query_string+=column_names_vector.at(col);
            if(col != column_names_vector.size() - 1)
                query_string+=",";
    }
    query_string+=") values (";
    for(int col = 0; col < column_names_vector.size(); col++){
        query_string+="'";
        query_string+=row.at(col)->text();
        query_string+="'";
            if(col != column_names_vector.size() - 1)
                query_string+=",";
    }
    query_string+=")";

    return query_string;
}

void DatabaseTableModel::save_row(QList<QStandardItem*> row){
    QSqlQuery query;
    QString string_query = prepare_update_query(row);
    qDebug()<<string_query << endl;
    query.exec(string_query);

    //query.exec(string_query);
}

void DatabaseTableModel::insertEmptyRow(){
    QList<QStandardItem*> row;
    for(int i = 0; i < columnCount(); i++){
        QStandardItem *item = new QStandardItem;
        item->setText("null");
        row.append(item);
    }
    fields.push_back(row);
    appendRow(row);
}






