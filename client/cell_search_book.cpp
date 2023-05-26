#include "cell_search_book.h"
#include "ui_cell_search_book.h"

Cell_Search_Book::Cell_Search_Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_Search_Book)
{
    ui->setupUi(this);
}

Cell_Search_Book::~Cell_Search_Book()
{
    delete ui;
}
