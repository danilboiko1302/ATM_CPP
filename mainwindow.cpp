#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableView>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     database ("databaseatm.csqvtipmkskj.eu-central-1.rds.amazonaws.com","ATM","danil_boiko","danil1302boiko"),
     ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    ui->mainWindow->setText("Hello");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_insertCard_clicked()
{
 bool ok;
 QString text;
 do{
      text = QInputDialog::getText(this, tr("Insert Card"),
                                             tr("Card: "), QLineEdit::Normal,
                                             "", &ok);
     if(!ok) return;
      qDebug() << text.length();
     if(text.length() != 16){
         QMessageBox::warning(this, tr("Error"),
                                        tr("Wrong input card"));
     }
     {
         bool res = false;
         Sequence <User> *w = &database.getUserAll();
         for(size_t i =0; i<w->sizes(); i++){
             for(size_t j =0; j<(*w)[i].getCards().sizes(); j++){
                 if((*w)[i].getCards()[j].getNumber() == text){
                     res = true;
                     database.setCurrentUser((*w)[i]);
                     break;
                 }
             }
             if(res) break;
         }
         if(!res){
             QMessageBox::warning(this, tr("Error"),
                                            tr("Can`t find card with this number"));
         } else {
             QMessageBox::information(this, tr("Greetings"),
                                            tr((*(new QString("Greetings: ")) + database.getCurrentUser().getName()).toUtf8().data()));
             ui->mainWindow->setText(*(new QString("Hello: ")) + database.getCurrentUser().getName());
             break;
         }
     }

 } while (text.length() != 16);


    qDebug() << ok;
}
