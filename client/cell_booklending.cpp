#include "cell_booklending.h"
#include "ui_cell_booklending.h"
#include "client.hpp"
#include <QDebug>
#include "foo.h"

Cell_BookLending::Cell_BookLending(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_BookLending)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    m_model.setHorizontalHeaderLabels(QStringList{"书籍编号","书名","借阅者","借书日期","应还日期"});

    //设置表格选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    client c;
    extern std::string acc;
    extern std::string psw;
    c.send_message(GET_MY_BOOK,acc.c_str(),psw.c_str()," ");

    std::vector<std::string> res = foo(c.get_return_buffer());

    int length = res.size();
    int column=5;
    int row=length/column;


    for (int i=0;i<row;i++) {
        QList<QStandardItem*> items;
        for (int j=0;j<column;j++) {
            int n=i*column+j;
            items.append(new QStandardItem(res.at(n).data()));
        }
        m_model.appendRow(items);
    }
}

Cell_BookLending::~Cell_BookLending()
{
    delete ui;
}
