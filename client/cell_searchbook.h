#ifndef CELL_SEARCHBOOK_H
#define CELL_SEARCHBOOK_H
#include <QStandardItemModel>

#include <QWidget>

namespace Ui {
class Cell_SearchBook;
}

class Cell_SearchBook : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_SearchBook(QWidget *parent = nullptr);
    ~Cell_SearchBook();
    void reset();

private slots:
    void on_btn_search_clicked();
    void onTableBtnClicked();


private:
    Ui::Cell_SearchBook *ui;
    QStandardItemModel m_model;
};

#endif // CELL_SEARCHBOOK_H
