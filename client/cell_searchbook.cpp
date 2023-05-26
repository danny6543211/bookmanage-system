#include "cell_searchbook.h"
#include "ui_cell_searchbook.h"
#include "client.hpp"
#include "dlg_login.h"
#include <QDebug>
#include <string>
#include "foo.h"
#include <QPushButton>
#include <QMessageBox>

Cell_SearchBook::Cell_SearchBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_SearchBook)
{
    ui->setupUi(this);

    ui->tableView->setModel(&m_model);

}

Cell_SearchBook::~Cell_SearchBook()
{
    delete ui;
}

void Cell_SearchBook::on_btn_search_clicked()
{
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"书籍编号","书名","是否在馆(1--在馆)","位置","操作"});
    //设置表格选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    char* bookname = ui->name_of_book->text().toUtf8().data();
    client c=client();

    extern std::string acc;
    extern std::string psw;

    c.send_message(9, acc.c_str(), psw.c_str(), bookname);
//    qDebug()<< c.get_return_value();
//    qDebug()<< c.get_return_buffer().c_str();

    std::vector<std::string> res = foo(c.get_return_buffer());
    qDebug()<<res.size();

    int length = res.size();
    int row=length/4;
    int column=4;

    for (int i=0;i<row;i++) {
        QList<QStandardItem*> items;
        for (int j=0;j<column;j++) {
            int n=i*column+j;
            items.append(new QStandardItem(res.at(n).data()));
        }
        m_model.appendRow(items);

        //往表格中添加按钮控件
        QPushButton *button = new QPushButton("借阅");
        //设置按钮属性 id=行数（从0开始）
        button->setProperty("id",i);
        button->setProperty("bookname",res.at(i*column+1).data());
        button->setProperty("state",res.at(i*column+2).data());

        //如果不在馆按钮不可点击
        if (button->property("state") == "0"){
            button->setEnabled(true);
        }

        //连接槽函数
        connect(button, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));

        //把按钮加到表格最后一列
        ui->tableView->setIndexWidget(m_model.index(m_model.rowCount()-1,column),button);
    }
}

void Cell_SearchBook::reset()
{
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"书籍编号","书名","是否在馆(1--在馆)","位置","操作"});
    //设置表格选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    char* bookname = ui->name_of_book->text().toUtf8().data();
    client c=client();

    extern std::string acc;
    extern std::string psw;

    c.send_message(9, acc.c_str(), psw.c_str(), bookname);
//    qDebug()<< c.get_return_value();
//    qDebug()<< c.get_return_buffer().c_str();

    std::vector<std::string> res = foo(c.get_return_buffer());
    qDebug()<<res.size();

    int length = res.size();
    int row=length/4;
    int column=4;

    for (int i=0;i<row;i++) {
        QList<QStandardItem*> items;
        for (int j=0;j<column;j++) {
            int n=i*column+j;
            items.append(new QStandardItem(res.at(n).data()));
        }
        m_model.appendRow(items);

        //往表格中添加按钮控件
        QPushButton *button = new QPushButton("借阅");
        //设置按钮属性 id=行数（从0开始）
        button->setProperty("id",i);
        button->setProperty("bookname",res.at(i*column+1).data());
        button->setProperty("state",res.at(i*column+2).data());

        //如果不在馆按钮不可点击
        if (button->property("state") == "0"){
            button->setEnabled(true);
        }

        //连接槽函数
        connect(button, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));

        //把按钮加到表格最后一列
        ui->tableView->setIndexWidget(m_model.index(m_model.rowCount()-1,column),button);
    }
}

void Cell_SearchBook::onTableBtnClicked(){

    extern std::string acc;
    extern std::string psw;

    //获取点击的按钮
    QPushButton *button = (QPushButton *)sender();
    char* name_of_book=button->property("bookname").toString().toLatin1().data();
    
//    qDebug()<<button->property("bookname").toString();
//    qDebug()<<name_of_book;


    client c;
    c.send_message(RENT_BOOK,acc.c_str(),psw.c_str(),name_of_book);

    if (c.get_return_value()==1){
        QMessageBox::information(this," ","借书成功");
    }
    reset();

}


