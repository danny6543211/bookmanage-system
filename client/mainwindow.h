#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cell_searchbook.h"
#include "cell_record.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initPage();
    void dealMenu();

private:
    Ui::MainWindow *ui;

    Cell_SearchBook *m_searchPage;
    Cell_Record *m_recordPage;
};
#endif // MAINWINDOW_H
