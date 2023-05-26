#ifndef CELL_RECORD_H
#define CELL_RECORD_H
#include <QStandardItemModel>

#include <QWidget>

namespace Ui {
class Cell_Record;
}

class Cell_Record : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_Record(QWidget *parent = nullptr);
    ~Cell_Record();
    void reset();

private slots:
    void onTableBtnClicked();

private:
    Ui::Cell_Record *ui;
    QStandardItemModel m_model;

};

#endif // CELL_RECORD_H
