#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include "databasetablemodel.h"
MainWindow::MainWindow(QString host, QString port, QString user, QString password,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setPort(port.toInt());

    model = new DatabaseTreeModel(db);
    ui->treeView->setModel(model);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete selected_table;
    db.close();
}


void MainWindow::render_table(const QModelIndex &index){
    QString schema = model->parent(index).data().toString();
    QString table = model->data(index).toString();
    DatabaseTableModel *tableModel = new DatabaseTableModel(db,schema,table);
    ui->tableView->setModel(tableModel);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if(!(model->hasChildren(index))){
        this->render_table(index);
        this->selected_table = &index;
    }
}


void MainWindow::on_saveButton_clicked()
{
    if(!selected_table){
        this->showNotification("Any table selected !");
        return;
    }

    DatabaseTableModel* model = static_cast<DatabaseTableModel*>(ui->tableView->model());
    model ->save_table();
    ui->tableView->update();
}

void MainWindow::showNotification(QString message){
    QMessageBox* message_box = new QMessageBox;
    message_box->setText(message);
    message_box->show();
}
