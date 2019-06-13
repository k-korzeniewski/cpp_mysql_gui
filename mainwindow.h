#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "databasetreemodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString host, QString port, QString user, QString passowrd,QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void render_table(const QModelIndex &index);

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    DatabaseTreeModel* model;
    const QModelIndex* selected_table;

    void showNotification(QString message);

};

#endif // MAINWINDOW_H
