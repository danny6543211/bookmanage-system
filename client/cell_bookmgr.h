#ifndef CELL_BOOKMGR_H
#define CELL_BOOKMGR_H
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class Cell_BookMgr;
}

class Cell_BookMgr : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_BookMgr(QWidget *parent = nullptr);
    ~Cell_BookMgr();

private slots:
    void on_btn_addBook_clicked();

private:
    Ui::Cell_BookMgr *ui;
    QStandardItemModel m_model;
};

#endif // CELL_BOOKMGR_H
