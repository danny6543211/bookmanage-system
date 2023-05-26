#include "mainwindow.h"
#include "mainwindow1.h"
#include <iostream>
#include <QDebug>
#include <QApplication>
#include "dlg_login.h"
#include <string>

#include "client.hpp"


using namespace std;

//全局变量账号和密码
string acc;
string psw;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    Dlg_Login dlg;
    int ret = dlg.exec();
    acc=dlg.acc;
    psw=dlg.psw;

    if(ret == 1)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }

    if(ret == 2)
    {
        MainWindow1 w;
        w.show();
        return a.exec();
    }
    if(ret == 0)
    {
        exit(0);
        return 0;
    }

    return 0;
}
