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
    setDefault();
   // debug
//    {
//        ui->mainWindow->show();
//        ui->empty->close();
//    }
    setWindowTitle("ATM");
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


    {
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
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSumCash(const int a)
{
    ui->sum->setText(QString::number(ui->sum->text().toInt() + a));
    ui->addCash->setText("Current amount: " + ui->sum->text() + "\n1 Confirm");
    wdg->close();
}

void MainWindow::b1()
{

    changeSumCash(1);
}

void MainWindow::b2()
{
     changeSumCash(2);
}
void MainWindow::b3()
{
   changeSumCash(5);
}
void MainWindow::b4()
{
     changeSumCash(10);
}
void MainWindow::b5()
{
     changeSumCash(20);
}
void MainWindow::b6()
{
     changeSumCash(50);
}
void MainWindow::b7()
{
     changeSumCash(100);
}
void MainWindow::b8()
{
    changeSumCash(200);
}
void MainWindow::b9()
{
     changeSumCash(500);
}
void MainWindow::b10()
{

     changeSumCash(1000);
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

         for(size_t i =0; i<database.getUserAll().sizes(); i++){
             for(size_t j =0; j<database.getUserAll()[i].getCards().sizes(); j++){
                 if(database.getUserAll()[i].getCards()[j].getNumber() == text){
                     res = true;
                     database.currentUser = (database.getUserAll()[i]);
                     database.currentCard = (database.getUserAll()[i].getCards()[j]);
                     break;
                 }
             }
             if(res) break;
         }
         qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
         qDebug() << database.currentUser.getCards().sizes();
         qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
         if(!res){
             QMessageBox::warning(this, tr("Error"),
                                            tr("Can`t find card with this number"));
         } else {
             if(database.currentCard.getStatus() == "block"){
                 QMessageBox::warning(this, tr("Error"),
                                                tr("This card is blocked"));
             } else {
                 QMessageBox::information(this, tr("Greetings"),
                                                tr((*(new QString("Greetings: ")) + database.currentUser.getName()).toUtf8().data()));
    //             ui->mainWindow->setText("Hello: " + database.getCurrentUser().getName()+"\n"+"Current card: "+ database.getCurrentCard().getNumber());
                 ui->firstWindow->setText("Enter PIN:\n");
                 ui->empty->close();
                 ui->firstWindow->show();
                 ui->pins->setText("3");
                  ui->insertCard->setDisabled(true);
                    setButtonOn();
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
        qDebug() << database.currentUser.getCards().sizes();
        for(size_t i = 0; i < database.currentUser.getCards().sizes(); ++i){
            char str1[11];
            sprintf(str1, "%d", i+1);
            ui->cards->setText(ui->cards->toPlainText() + str1 + " " + database.currentUser.getCards()[i].getNumber()+"\n");
            qDebug() << database.currentUser.getCards().sizes();
        }
        ui->cards->setText(ui->cards->toPlainText() + "8 Exit");


    } else if(!ui->cards->isHidden()){
         checkBlockCard(0);

    } else if(!ui->cash->isHidden()){
        giveCash(50);
    } else if(!ui->addCash->isHidden()){
        giveCash(-(ui->sum->text().toInt()));
        ui->addCash->close();
        ui->mainWindow->show();
        ui->sum->setText("0");
    }

}
void MainWindow::on_screen2_clicked()
{
    if(!ui->mainWindow->isHidden()){
        char str1[11];
        sprintf(str1, "%d", database.currentCard.getBalance());
        QString temp ("Balance for current card is ");
        temp += str1;
        QMessageBox::information(this, tr("Balance"),
                                       tr(temp.toUtf8().data()));

    } else if(!ui->cards->isHidden()){

             checkBlockCard(1);

        } else if(!ui->cash->isHidden()){
        giveCash(100);
    }
}

void MainWindow::on_screen3_clicked()
{
    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->close();
        ui->cash->show();

    } else if(!ui->cards->isHidden()){
            checkBlockCard(2);

        } else if(!ui->cash->isHidden()){
       giveCash(200);
    }
}
void MainWindow::on_screen4_clicked()
{

    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->close();
        ui->addCash->show();

        ui->insertCash->setDisabled(false);
        ui->addCash->setText("Current amount: " + ui->sum->text() + "\n1 Confirm");

    } else if(!ui->cards->isHidden()){
             checkBlockCard(3);

        } else if(!ui->cash->isHidden()){
          giveCash(500);
    }
}

void MainWindow::on_screen5_clicked()
{
    if(!ui->mainWindow->isHidden()){
        bool ok;
        QString card;
        int amount;
        do{
             card = QInputDialog::getText(this, tr("Input Card"),
                                                    tr("Card: "), QLineEdit::Normal,
                                                    "", &ok);
            if(!ok) return;
             qDebug() << card.length();
              qDebug() << card.toULongLong();
            if(card.length() != 16 || card.toULongLong() == 0){
                QMessageBox::warning(this, tr("Error"),
                                               tr("Wrong input card"));
            }

        } while (card.length() != 16 || card.toULongLong() == 0);
        do{
             amount = QInputDialog::getInt(this, tr("Input Amount"),
                                                    tr("Amount: "), QLineEdit::Normal
                                                    );

             if(amount == 0) return;
            if(amount < 0){
                QMessageBox::warning(this, tr("Error"),
                                               tr("Wrong input amount"));
            }

        } while (amount < 0);

        database.sendMoney(database.currentCard.getNumber(), card, amount);

    } else if(!ui->cards->isHidden()){
             checkBlockCard(4);

        } else if(!ui->cash->isHidden()){
        giveCash(1000);
    }
}
void MainWindow::on_screen6_clicked()
{
    if(!ui->mainWindow->isHidden()){
        QMessageBox msgBox;
        QString temp ("You want to block your current card ");
        temp += database.currentCard.getNumber();
        msgBox.setText(temp);
        msgBox.setInformativeText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Ok:
              // Save was clicked
               database.blockCard(database.currentCard.getNumber());
               QMessageBox::warning(this, tr("Error"),
                                              tr("Your Card is Blocked now"));
               setDefault();

              break;
          case QMessageBox::Cancel:
              break;
          default:
              // should never be reached
              break;
        }

    } else if(!ui->cards->isHidden()){
            checkBlockCard(5);

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
            giveCash(res);
        }

    }
}

void MainWindow::on_screen7_clicked()
{
    if(!ui->mainWindow->isHidden()){
        bool ok;
         int res;
        QString text;
        do{
             text = QInputDialog::getText(this, tr("Insert new Pin"),
                                                    tr("Pin: "), QLineEdit::Normal,
                                                    "", &ok);
            if(!ok) return;
             qDebug() << text.length();
            if(text.length() < 4){
                QMessageBox::warning(this, tr("Error"),
                                               tr("Pin is too short"));
            }else
            {
                 res = text.toInt();
                if (res <= 0){
                    QMessageBox::warning(this, tr("Error"),
                                                   tr("Wrong input"));
                } else {
                    QMessageBox msgBox;
                    QString temp ("You want to change pin on your current card ");
                    temp += database.currentCard.getNumber();
                    msgBox.setText(temp);
                    msgBox.setInformativeText("Are you sure?");
                    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                    msgBox.setDefaultButton(QMessageBox::Cancel);
                    int ret = msgBox.exec();
                    switch (ret) {
                      case QMessageBox::Ok:
                          // Ok was clicked

                        database.changePin(database.currentCard.getNumber(), QString::number(res));
                           QMessageBox::information(this, tr("Pin"),
                                                          tr("Pin in changed"));
                           setDefault();
                          break;
                      case QMessageBox::Cancel:
                          break;
                      default:
                          // should never be reached
                          break;
                    }
                }
            }


        } while (text.length() < 4 || res <= 0);

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
     if( ui->pin->toPlainText() == database.currentCard.getPin()){
         QMessageBox::information(this, tr("Wlecome"),
                                        tr("PIN is correct"));
         setButtonOff();

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
             database.blockCard(database.currentCard.getNumber());

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
    setButtonOff();
    ui->empty->show();
   }
}



void MainWindow::on_insertCash_clicked()
{
    wdg->show();
}

void MainWindow::setButtonOff()
{
    ui->b1->setDisabled(true);
    ui->b2->setDisabled(true);
    ui->b3->setDisabled(true);
    ui->b4->setDisabled(true);
    ui->b5->setDisabled(true);
    ui->b6->setDisabled(true);
    ui->b7->setDisabled(true);
    ui->b8->setDisabled(true);
    ui->b9->setDisabled(true);
    ui->ok->setDisabled(true);
    ui->reset->setDisabled(true);
    ui->cancel->setDisabled(true);
}

void MainWindow::setButtonOn()
{
    ui->b1->setDisabled(false);
    ui->b2->setDisabled(false);
    ui->b3->setDisabled(false);
    ui->b4->setDisabled(false);
    ui->b5->setDisabled(false);
    ui->b6->setDisabled(false);
    ui->b7->setDisabled(false);
    ui->b8->setDisabled(false);
    ui->b9->setDisabled(false);
    ui->ok->setDisabled(false);
    ui->reset->setDisabled(false);
    ui->cancel->setDisabled(false);
}



void MainWindow::setDefault()
{
    ui->firstWindow->close();
    ui->mainWindow->close();
    ui->pin->close();
    ui->cash->close();


    ui->cards->close();
    ui->addCash->close();
    ui->insertCash->setDisabled(true);
    ui->pin->close();
    ui->pins->close();
    ui->sum->close();
    ui->empty->show();
    ui->insertCard->setDisabled(false);
    ui->b1->setDisabled(true);
    ui->b2->setDisabled(true);
    ui->b3->setDisabled(true);
    ui->b4->setDisabled(true);
    ui->b5->setDisabled(true);
    ui->b6->setDisabled(true);
    ui->b7->setDisabled(true);
    ui->b8->setDisabled(true);
    ui->b9->setDisabled(true);
    ui->ok->setDisabled(true);
    ui->reset->setDisabled(true);
    ui->cancel->setDisabled(true);
}

void MainWindow::checkBlockCard(const size_t a)
{
    if(database.currentUser.getCards().sizes() > a){
        if(database.currentUser.getCards()[a].getStatus() == "block"){
            QMessageBox::warning(this, tr("Error"),
                                           tr("This card is blocked"));
        } else {
            database.currentCard = (database.currentUser.getCards()[a]);
            ui->mainWindow->show();
            ui->cards->close();
        }

    }
}

void MainWindow::giveCash(const int a)
{
    if (database.currentCard.getBalance() < a){
        QMessageBox::warning(this, tr("Error"),
                                       tr("Not enough money"));
    } else {
        database.getCash(a);
        if(a > 0){
            QString temp ("You got ");
            temp+=QString::number(a);
            temp+=" dollars";
            QMessageBox::information(this, tr("Cash"),
                                           tr(temp.toUtf8().data()));
        } else {
            char str1[11];
            sprintf(str1, "%d", database.currentCard.getBalance());
            QString temp ("Balance for current card is ");
            temp += str1;
            QMessageBox::information(this, tr("Balance"),
                                           tr(temp.toUtf8().data()));
        }

    }
}


