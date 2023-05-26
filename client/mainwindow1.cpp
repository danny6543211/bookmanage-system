#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QPushButton>
#include <QDebug>

MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow1)
    ,m_userPage(nullptr)
    ,m_bookPage(nullptr)
    ,m_bookLendingPage(nullptr)
{
    ui->setupUi(this);
    initPage();
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::initPage()

{
//    m_userPage = new Cell_UserMgr(this);
    m_bookPage = new Cell_BookMgr(this);
    m_bookLendingPage = new Cell_BookLending(this);


//    ui->stackedWidget->addWidget(m_userPage);
    ui->stackedWidget->addWidget(m_bookPage);
    ui->stackedWidget->addWidget(m_bookLendingPage);



    auto l = ui->tool->children();
    for(auto it:l)
    {
        if (it->objectName().contains("btn"))
        {
            connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&MainWindow1::dealMenu);
        }
    }
}

void MainWindow1::dealMenu()
{
    auto str = sender()->objectName();
    do
    {
        if(str == "btn_user")
        {
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }
        if(str == "btn_book")
        {
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }
        if(str == "btn_bookLending")
        {
            ui->stackedWidget->setCurrentIndex(2);
            break;
        }

    }while(false);
}
