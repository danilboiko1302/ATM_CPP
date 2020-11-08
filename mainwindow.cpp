#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->insertCash->setDisabled(true);
   // debug
    {
        ui->mainWindow->show();
        ui->empty->close();
    }

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

void MainWindow::b1()
{
    qDebug() << "1";
    wdg->close();

}

void MainWindow::b2()
{

}
void MainWindow::b3()
{

}
void MainWindow::b4()
{

}
void MainWindow::b5()
{

}
void MainWindow::b6()
{

}
void MainWindow::b7()
{

}
void MainWindow::b8()
{

}
void MainWindow::b9()
{

}
void MainWindow::b10()
{

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
            QMessageBox::information(this, tr("Cash"),
                                           tr("You got 50 dollars"));
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
            QMessageBox::information(this, tr("Cash"),
                                           tr("You got 100 dollars"));
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
            QMessageBox::information(this, tr("Cash"),
                                           tr("You got 200 dollars"));
        }
    }
}
void MainWindow::on_screen4_clicked()
{

    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->close();

        ui->insertCash->setDisabled(false);

    } else if(!ui->cards->isHidden()){
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
            QMessageBox::information(this, tr("Cash"),
                                           tr("You got 500 dollars"));
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
            QMessageBox::information(this, tr("Cash"),
                                           tr("You got 1000 dollars"));
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

        } else if(!ui->cash->isHidden()){
        bool ok;
        int res;
        do{
            ok = true;
             res = QInputDialog::getInt(this, tr("Choose amount multiple of 50"),
                                                    tr(""), QLineEdit::Normal);
             if (res < 0 ){
                 QMessageBox::warning(this, tr("Error"),
                                                tr("Amount must be more than 0"));
                  ok = false;
             } else if(res % 50 != 0){
                ok = false;
                QMessageBox::warning(this, tr("Error"),
                                               tr("Amount must be multiple of 50"));
            }
             qDebug() << res;
        } while(res < 0 || !ok);
        if(res != 0){
            if (database.getCurrentCard().getBalance() < res){
                QMessageBox::warning(this, tr("Error"),
                                               tr("Not enough money"));
            } else {
                database.getCash(res);
                QString temp ("You got ");
                temp +=  QString::number(res);
                temp += " dollars";
                QMessageBox::information(this, tr("Cash"),
                                               tr(temp.toUtf8().data()));

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



void MainWindow::on_insertCash_clicked()
{


    //hide();
    QGridLayout *layout = new QGridLayout();
    QPushButton *b1 = new QPushButton();
    QPushButton *b2 = new QPushButton();
    QPushButton *b3 = new QPushButton();
    QPushButton *b4 = new QPushButton();
    QPushButton *b5 = new QPushButton();
    QPushButton *b6 = new QPushButton();
    QPushButton *b7 = new QPushButton();
    QPushButton *b8 = new QPushButton();
    QPushButton *b9 = new QPushButton();
    QPushButton *b10 = new QPushButton();
    b1->setText("1");
    b2->setText("2");
    b3->setText("5");
    b4->setText("10");
    b5->setText("20");
    b6->setText("50");
    b7->setText("100");
    b8->setText("200");
    b9->setText("500");
    b10->setText("1000");
    connect(b1, SIGNAL (clicked()), this, SLOT (b1()));
    connect(b2, SIGNAL (clicked()), this, SLOT (b2()));
    connect(b3, SIGNAL (clicked()), this, SLOT (b3()));
    connect(b4, SIGNAL (clicked()), this, SLOT (b4()));
    connect(b5, SIGNAL (clicked()), this, SLOT (b5()));
    connect(b6, SIGNAL (clicked()), this, SLOT (b6()));
    connect(b7, SIGNAL (clicked()), this, SLOT (b7()));
    connect(b8, SIGNAL (clicked()), this, SLOT (b8()));
    connect(b9, SIGNAL (clicked()), this, SLOT (b9()));
    connect(b10, SIGNAL (clicked()), this, SLOT (b10()));
    layout->addWidget(b1);
    layout->addWidget(b2);
    layout->addWidget(b3);
    layout->addWidget(b4);
    layout->addWidget(b5);
    layout->addWidget(b6);
    layout->addWidget(b7);
    layout->addWidget(b8);
    layout->addWidget(b9);
    layout->addWidget(b10);
    wdg->setLayout(layout);
    wdg->show();
    //a->on_pushButton_clicked();
}
