#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Db.h"
#include <QTableView>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Db test ("databaseatm.csqvtipmkskj.eu-central-1.rds.amazonaws.com","ATM","danil_boiko","danil1302boiko");
  // test.getUserAll().show();
   // QString aa = "123";
   // Card testdf ();

}

MainWindow::~MainWindow()
{
    delete ui;
}

