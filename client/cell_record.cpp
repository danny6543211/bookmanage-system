#include "cell_record.h"
#include "ui_cell_record.h"
#include "client.hpp"
#include <QDebug>
#include <vector>
#include "foo.h"
#include <QPushButton>
#include <QMessageBox>

Cell_Record::Cell_Record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_Record)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);

    m_model.setHorizontalHeaderLabels(QStringList{"书籍编号","书名","借书日期","应还日期","操作"});
    //设置表格选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnWidth(2, 150);
    ui->tableView->setColumnWidth(3, 150);

    client c;
    extern std::string acc;
    extern std::string psw;
    c.send_message(GET_MY_BOOK,acc.c_str(),psw.c_str()," ");
    qDebug()<<c.get_return_buffer().c_str();

    std::vector<std::string> res = foo(c.get_return_buffer());
//    for (std::string str : res)
//    {
//        std::cout << str << std::endl;
//    }



    int length = res.size();
//    qDebug()<<length;
    int column=4;
    int row=length/column;


    for (int i=0;i<row;i++) {
        QList<QStandardItem*> items;
        for (int j=0;j<column;j++) {
            int n=i*column+j;
            items.append(new QStandardItem(res.at(n).data()));
        }
        m_model.appendRow(items);

        //往表格中添加按钮控件
        QPushButton *button = new QPushButton("归还");
        //设置按钮属性 id=行数（从0开始）
        button->setProperty("id",i);
        button->setProperty("bookname",res.at(i*column+1).data());
        button->setProperty("state",res.at(i*column+2).data());

        //连接槽函数
        connect(button, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));

        //把按钮加到表格最后一列
        ui->tableView->setIndexWidget(m_model.index(m_model.rowCount()-1,column),button);
    }
}

void Cell_Record::reset()
{
    m_model.clear();

    m_model.setHorizontalHeaderLabels(QStringList{"书籍编号","书名","借书日期","应还日期","操作"});
    //设置表格选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnWidth(2, 155);
    ui->tableView->setColumnWidth(3, 155);

    client c;
    extern std::string acc;
    extern std::string psw;
    c.send_message(GET_MY_BOOK,acc.c_str(),psw.c_str()," ");
    qDebug()<<c.get_return_buffer().c_str();

    std::vector<std::string> res = foo(c.get_return_buffer());
//    for (std::string str : res)
//    {
//        std::cout << str << std::endl;
//    }



    int length = res.size();
//    qDebug()<<length;
    int column=4;
    int row=length/column;


    for (int i=0;i<row;i++) {
        QList<QStandardItem*> items;
        for (int j=0;j<column;j++) {
            int n=i*column+j;
            items.append(new QStandardItem(res.at(n).data()));
        }
        m_model.appendRow(items);

        //往表格中添加按钮控件
        QPushButton *button = new QPushButton("归还");
        //设置按钮属性 id=行数（从0开始）
        button->setProperty("id",i);
        button->setProperty("bookname",res.at(i*column+1).data());
        button->setProperty("state",res.at(i*column+2).data());

        //连接槽函数
        connect(button, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));

        //把按钮加到表格最后一列
        ui->tableView->setIndexWidget(m_model.index(m_model.rowCount()-1,column),button);
    }
}

void Cell_Record::onTableBtnClicked(){
    extern std::string acc;
    extern std::string psw;

    //获取点击的按钮
    QPushButton *button = (QPushButton *)sender();
    const char* name_of_book=button->property("bookname").toString().toStdString().c_str();
    char* bookname=new char[20];
    strcpy(bookname,name_of_book);
    qDebug()<<button->property("bookname").toString();


    client c;
    c.send_message(RETURN_BOOK,acc.c_str(),psw.c_str(),bookname);

    qDebug()<<"return"<<c.get_return_value();

    //还书成功返回值是？
    if (c.get_return_value()==1){
        QMessageBox::information(this," ","归还成功");
        m_model.removeRow(button->property("id").toInt());
    }
}

Cell_Record::~Cell_Record()
{
    delete ui;
}
