#include "dlg_login.h"
#include "ui_dlg_login.h"
#include <QDebug>
#include <string>
#include <iostream>
#include "client.hpp"
#include "message.hpp"
#include "mainwindow.h"
#include "mainwindow1.h"
#include <QMessageBox>



using namespace std;

Dlg_Login::Dlg_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Login)
{
    ui->setupUi(this);
}

Dlg_Login::~Dlg_Login()
{
    delete ui;
}

void Dlg_Login::on_LogInButton_clicked()
{
//    char *account =  ui->accountName->text().toUtf8().data();
//    char *password =  ui->password->text().toUtf8().data();

    char *account =  ui->accountName->text().toLatin1().data();
    char *password =  ui->password->text().toLatin1().data();

    std::cout << account << std::endl;
    std::cout << password << std::endl;


    client login;
    login.send_message(LOG_IN, account, password, " ");
    int res = login.get_return_value();
    string authority = login.get_return_buffer();
    if (res == 0 || res == -1){
        QMessageBox::critical(this," ","密码或密碼错误");
    }
    else{
        if (!(strcmp(authority.c_str(),"manager"))){
            setResult(2);
            this->acc=account;
            this->psw=password;
            hide();
        }
        else if (!(strcmp(authority.c_str(),"user"))){
            setResult(1);
            this->acc=account;
            this->psw=password;
            hide();
        }
        else {
            setResult(0);
            hide();
        }
    }
}

void Dlg_Login::on_ExitButton_clicked()
{
    setResult(0);
    hide();
}

void Dlg_Login::on_RegisterButton_clicked()
{
    char *account =  ui->accountName->text().toUtf8().data();
    char *password =  ui->password->text().toUtf8().data();
    client reg;
    reg.send_message(SIGN_UP,account,password," ");

    if (reg.get_return_value()==1){
        QMessageBox::information(this, " ","注册成功");
    }
}
