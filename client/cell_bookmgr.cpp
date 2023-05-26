#include "cell_bookmgr.h"
#include "ui_cell_bookmgr.h"
#include "client.hpp"
#include <QDebug>
#include <QMessageBox>


Cell_BookMgr::Cell_BookMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_BookMgr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    m_model.setHorizontalHeaderLabels(QStringList{"书籍编号","书名","位置","操作"});
    client c;
//    c.send_message()
}

Cell_BookMgr::~Cell_BookMgr()
{
    delete ui;
}

void Cell_BookMgr::on_btn_addBook_clicked()
{
    client c;
    extern std::string acc;
    extern std::string psw;
    char* bookname=ui->add_bookname->text().toUtf8().data();
    c.send_message(5,acc.c_str(),psw.c_str(),bookname);
    if(c.get_return_value()==1){
        QMessageBox::information(this," ","添加成功");
    }


}
