#ifndef CELL_USERMGR_H
#define CELL_USERMGR_H

#include <QWidget>

namespace Ui {
class Cell_UserMgr;
}

class Cell_UserMgr : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_UserMgr(QWidget *parent = nullptr);
    ~Cell_UserMgr();

private:
    Ui::Cell_UserMgr *ui;
};

#endif // CELL_USERMGR_H
