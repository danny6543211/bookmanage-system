#include "cell_usermgr.h"
#include "ui_cell_usermgr.h"
#include "client.hpp"

Cell_UserMgr::Cell_UserMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_UserMgr)
{
    ui->setupUi(this);
    client c;
//    c.send_message()
}

Cell_UserMgr::~Cell_UserMgr()
{
    delete ui;
}
