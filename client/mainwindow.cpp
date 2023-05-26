#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include "client.hpp"
#include "foo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_searchPage(nullptr)
    ,m_recordPage(nullptr)
{
    ui->setupUi(this);
    initPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPage()
{

    m_searchPage = new Cell_SearchBook(this);
    m_recordPage = new Cell_Record(this);

    ui->stackedWidget->addWidget(m_searchPage);
    ui->stackedWidget->addWidget(m_recordPage);

    auto l = ui->tool->children();
    for(auto it:l)
    {
        if (it->objectName().contains("btn"))
        {
            connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&MainWindow::dealMenu);
        }
    }

    m_searchPage->reset();
}

void MainWindow::dealMenu()
{
    auto str = sender()->objectName();
    do
    {
        if(str == "btn_book")
        {
            ui->stackedWidget->setCurrentIndex(0);
            m_searchPage->reset();
            break;
        }

        if(str == "btn_record")
        {
            ui->stackedWidget->setCurrentIndex(1);
            m_recordPage->reset();
            break;
        }
    }while(false);
}

