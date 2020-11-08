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
    ui->cash->close();
    ui->trans->close();
    ui->cards->close();
   // debug
//    {
//        ui->mainWindow->show();
//        ui->empty->close();
//    }

    ui->mainWindow->setText("1 Change card\n\n"
                      "2 Check balance\n\n"
                      "3 Get cash\n\n"
                      "4 Card replenishment\n\n"
                      "5 Card transfer\n\n"
                      "6 Block card\n\n"
                      "7 Change PIN \n\n"
                      "8 Other");
    ui->cash->setText("1 50\n\n"
                      "2 100\n\n"
                      "3 200\n\n"
                      "4 500\n\n"
                      "5 1000\n\n"
                      "6 another amount\n\n"
                      "8 Exit"
                      );

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

    if(!ui->mainWindow->isHidden()){
        ui->cards->setText("");

        ui->mainWindow->close();
        ui->cards->show();
        for(size_t i = 0; i < database.getCurrentUser().getCards().sizes(); ++i){
            char str1[11];
            sprintf(str1, "%d", i+1);
            ui->cards->setText(ui->cards->toPlainText() + str1 + " " + database.getCurrentUser().getCards()[i].getNumber()+"\n");
            qDebug() << database.getCurrentUser().getCards().sizes();
        }
        ui->cards->setText(ui->cards->toPlainText() + "8 Exit");


    } else if(!ui->cards->isHidden()){
        if(database.getCurrentUser().getCards().sizes() > 0){
            if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                QMessageBox::warning(this, tr("Error"),
                                               tr("This card is blocked"));
            } else {
                database.setCurrentCard(database.getCurrentUser().getCards()[0]);
                ui->mainWindow->show();
                ui->cards->close();
            }

        }

    } else if(!ui->cash->isHidden()){
        if (database.getCurrentCard().getBalance() < 50){
            QMessageBox::warning(this, tr("Error"),
                                           tr("Not enough money"));
        } else {
            database.getCash(50);
        }
    }

}
void MainWindow::on_screen2_clicked()
{
    if(!ui->mainWindow->isHidden()){
        char str1[11];
        sprintf(str1, "%d", database.getCurrentCard().getBalance());
        QString temp ("Balance for current card is ");
        temp += str1;
        QMessageBox::information(this, tr("Balance"),
                                       tr(temp.toUtf8().data()));

    } else if(!ui->cards->isHidden()){
            if(database.getCurrentUser().getCards().sizes() > 1){
                if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("This card is blocked"));
                } else {
                    database.setCurrentCard(database.getCurrentUser().getCards()[1]);
                    ui->mainWindow->show();
                    ui->cards->close();
                }

            }

        } else if(!ui->cash->isHidden()){
        if (database.getCurrentCard().getBalance() < 100){
            QMessageBox::warning(this, tr("Error"),
                                           tr("Not enough money"));
        } else {
            database.getCash(100);
        }
    }
}

void MainWindow::on_screen3_clicked()
{
    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->close();
        ui->cash->show();

    } else if(!ui->cards->isHidden()){
            if(database.getCurrentUser().getCards().sizes() > 2){
                if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("This card is blocked"));
                } else {
                    database.setCurrentCard(database.getCurrentUser().getCards()[2]);
                    ui->mainWindow->show();
                    ui->cards->close();
                }

            }

        } else if(!ui->cash->isHidden()){
        if (database.getCurrentCard().getBalance() < 200){
            QMessageBox::warning(this, tr("Error"),
                                           tr("Not enough money"));
        } else {
            database.getCash(200);
        }
    }
}
void MainWindow::on_screen4_clicked()
{
    if(!ui->cards->isHidden()){
            if(database.getCurrentUser().getCards().sizes() > 3){
                if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("This card is blocked"));
                } else {
                    database.setCurrentCard(database.getCurrentUser().getCards()[3]);
                    ui->mainWindow->show();
                    ui->cards->close();
                }

            }

        } else if(!ui->cash->isHidden()){
        if (database.getCurrentCard().getBalance() < 500){
            QMessageBox::warning(this, tr("Error"),
                                           tr("Not enough money"));
        } else {
            database.getCash(500);
        }
    }
}

void MainWindow::on_screen5_clicked()
{
    if(!ui->cards->isHidden()){
            if(database.getCurrentUser().getCards().sizes() > 4){
                if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("This card is blocked"));
                } else {
                    database.setCurrentCard(database.getCurrentUser().getCards()[4]);
                    ui->mainWindow->show();
                    ui->cards->close();
                }

            }

        } else if(!ui->cash->isHidden()){
        if (database.getCurrentCard().getBalance() < 1000){
            QMessageBox::warning(this, tr("Error"),
                                           tr("Not enough money"));
        } else {
            database.getCash(1000);
        }
    }
}
void MainWindow::on_screen6_clicked()
{
    if(!ui->cards->isHidden()){
            if(database.getCurrentUser().getCards().sizes() > 5){
                if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("This card is blocked"));
                } else {
                    database.setCurrentCard(database.getCurrentUser().getCards()[5]);
                    ui->mainWindow->show();
                    ui->cards->close();
                }

            }

        }
}

void MainWindow::on_screen7_clicked()
{
    if(!ui->cards->isHidden()){
            if(database.getCurrentUser().getCards().sizes() > 6){
                if(database.getCurrentUser().getCards()[0].getStatus() == "blocked"){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("This card is blocked"));
                } else {
                    database.setCurrentCard(database.getCurrentUser().getCards()[6]);
                    ui->mainWindow->show();
                    ui->cards->close();
                }

            }

        }
}
void MainWindow::on_screen8_clicked()
{
    if(!ui->cards->isHidden()){
        ui->mainWindow->show();
        ui->cards->close();

    } else if(!ui->cash->isHidden()){
        ui->mainWindow->show();
        ui->cash->close();

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


