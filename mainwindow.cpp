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
    ui->firstWindow->close();
    ui->mainWindow->close();
    ui->pin->close();
   database.getUserAll().show();

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
     }else
     {
         bool res = false;
         Sequence <User> *w = &database.getUserAll();
         for(size_t i =0; i<w->sizes(); i++){
             for(size_t j =0; j<(*w)[i].getCards().sizes(); j++){
                 if((*w)[i].getCards()[j].getNumber() == text){
                     res = true;
                     database.setCurrentUser((*w)[i]);
                     database.setCurrentCard((*w)[i].getCards()[j]);
                     break;
                 }
             }
             if(res) break;
         }
         if(!res){
             QMessageBox::warning(this, tr("Error"),
                                            tr("Can`t find card with this number"));
         } else {
             if(database.getCurrentCard().getStatus() == "block"){
                 QMessageBox::warning(this, tr("Error"),
                                                tr("This card is blocked"));
             } else {
                 QMessageBox::information(this, tr("Greetings"),
                                                tr((*(new QString("Greetings: ")) + database.getCurrentUser().getName()).toUtf8().data()));
    //             ui->mainWindow->setText("Hello: " + database.getCurrentUser().getName()+"\n"+"Current card: "+ database.getCurrentCard().getNumber());
                 ui->firstWindow->setText("Enter PIN:\n");
                 ui->empty->close();
                 ui->firstWindow->show();
                 ui->pins->setText("3");
                  ui->insertCard->setDisabled(true);
                 break;
             }

         }
     }

 } while (text.length() != 16);



}

void MainWindow::on_screen1_clicked()
{

    if(!ui->cash->isHidden()){

    } else if(!ui->trans->isHidden()){

    }

}



void MainWindow::on_b1_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
 ui->pin->setText(ui->pin->toPlainText() + "1");
}

void MainWindow::on_b2_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "2");
}

void MainWindow::on_b3_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "3");
}
void MainWindow::on_b4_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "4");
}
void MainWindow::on_b5_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "5");
}
void MainWindow::on_b6_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "6");
}
void MainWindow::on_b7_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "7");
}
void MainWindow::on_b8_clicked()
{
     ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
ui->pin->setText(ui->pin->toPlainText() + "8");
}
void MainWindow::on_b9_clicked()
{
 ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
    ui->pin->setText(ui->pin->toPlainText() + "9");
}

void MainWindow::on_ok_clicked()
{   if(!ui->firstWindow->isHidden()) {
     if( ui->pin->toPlainText() == database.getCurrentCard().getPin()){
         QMessageBox::information(this, tr("Wlecome"),
                                        tr("PIN is correct"));
         ui->firstWindow->close();
         ui->mainWindow->show();

         ui->empty->close();
     } else{
         QMessageBox::warning(this, tr("Error"),
                                        tr("Wrong PIN"));
         if(ui->pins->text() == "3"){
             ui->pins->setText("2");
         } else  if(ui->pins->text() == "2"){
             ui->pins->setText("1");
         } else  {
             QMessageBox::warning(this, tr("Error"),
                                            tr("Your Card is Blocked now"));
             database.blockCard(database.getCurrentCard().getNumber());

             ui->pin->setText("");
             ui->firstWindow->close();
             ui->mainWindow->close();
 ui->insertCard->setDisabled(true);
             ui->empty->show();

         }
     }
    ui->pin->setText("");
    ui->firstWindow->setText("Enter PIN:\n");
    }
}
void MainWindow::on_reset_clicked()
{
    if(!ui->firstWindow->isHidden()) {
 ui->pin->setText("");
 ui->firstWindow->setText("Enter PIN:\n");
    }
}

void MainWindow::on_cancel_clicked()
{
   if(!ui->firstWindow->isHidden()) {
    ui->pin->setText("");
    ui->firstWindow->close();
    ui->mainWindow->close();
    ui->insertCard->setDisabled(false);
    ui->empty->show();
   }
}
