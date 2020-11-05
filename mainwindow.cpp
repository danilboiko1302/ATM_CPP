#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Db.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Db test ("databaseatm.csqvtipmkskj.eu-central-1.rds.amazonaws.com","ATM","danil_boiko","danil1302boiko");
    ui->label->setText(test.check());
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("databaseatm.csqvtipmkskj.eu-central-1.rds.amazonaws.com");
//    db.setDatabaseName("ATM");
//    db.setUserName("danil_boiko");
//    db.setPassword("danil1302boiko");
//    bool ok = db.open();
//    cout<<db.hostName().data()<<endl;
//    if(ok)
//    {
//        ui->label->setText("Connected");
//    }
//    else
//    {
//        ui->label->setText("Not Connected");
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

