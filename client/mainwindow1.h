#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include "cell_usermgr.h"
#include "cell_bookmgr.h"
#include "cell_booklending.h"
#include "cell_record.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow1; }
QT_END_NAMESPACE



class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
    void initPage();
    void dealMenu();

private:
    Ui::MainWindow1 *ui;
    Cell_UserMgr *m_userPage;
    Cell_BookMgr *m_bookPage;
    Cell_BookLending *m_bookLendingPage;
    Cell_Record *m_recordPage;
};

#endif // MAINWINDOW1_H
