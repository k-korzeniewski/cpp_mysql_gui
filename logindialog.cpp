#include "logindialog.h"
#include "mainwindow.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
    QString host = ui->hostInput->text();
    QString port = ui->portInput->text();
    QString userName = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    MainWindow* window = new MainWindow(host,port,userName,password);
    window->setWindowTitle("DATABASE");
    window->show();
}
