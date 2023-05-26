#ifndef CELL_SEARCH_BOOK_H
#define CELL_SEARCH_BOOK_H

#include <QWidget>

namespace Ui {
class Cell_Search_Book;
}

class Cell_Search_Book : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_Search_Book(QWidget *parent = nullptr);
    ~Cell_Search_Book();

private:
    Ui::Cell_Search_Book *ui;
};

#endif // CELL_SEARCH_BOOK_H
