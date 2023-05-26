#ifndef CELL_BOOKLENDING_H
#define CELL_BOOKLENDING_H

#include <QStandardItemModel>

#include <QWidget>

namespace Ui {
class Cell_BookLending;
}

class Cell_BookLending : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_BookLending(QWidget *parent = nullptr);
    ~Cell_BookLending();

private:
    Ui::Cell_BookLending *ui;
    QStandardItemModel m_model;
};

#endif // CELL_BOOKLENDING_H
