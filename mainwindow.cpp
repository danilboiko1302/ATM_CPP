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
    this->setFixedSize(this->width(), this->height());
    ui->mainWindow->setText("1 Change card\n\n"
                            "2 Check balance\n\n"
                            "3 Get cash\n\n"
                            "4 Card replenishment\n\n"
                            "5 Card transfer\n\n"
                            "6 Block card\n\n"
                            "7 Change PIN \n\n"
                            "8 Other");
    ui->mainWindow->setText("1 Check balance\n\n"
                            "2 Get cash\n\n"
                            "3 Card replenishment\n\n"
                            "4 Card transfer\n\n"
                            "5 Block card\n\n"
                            "6 Change PIN \n\n"
                            "7 Other\n\n"
                            "8 Exit");


    ui->cash->setText("1 50\n\n"
                      "2 100\n\n"
                      "3 200\n\n"
                      "4 500\n\n"
                      "5 1000\n\n"
                      "6 another amount\n\n"
                      "8 Return"
                      );
    ui->other->setText("1 Phone number replenishment\n\n"
                       "2 Charity\n\n"
                       "3 Extract\n\n"
                       "8 Return");



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
        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        connect(b1, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b2, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b3, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b4, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b5, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b6, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b7, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b8, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b9, SIGNAL (clicked()), signalMapper, SLOT (map()));
        connect(b10, SIGNAL (clicked()), signalMapper, SLOT (map()));
        signalMapper -> setMapping (b1, 1);
        signalMapper -> setMapping (b2, 2);
        signalMapper -> setMapping (b3, 5) ;
        signalMapper -> setMapping (b4, 10) ;
        signalMapper -> setMapping (b5, 20) ;
        signalMapper -> setMapping (b6, 50) ;
        signalMapper -> setMapping (b7, 100) ;
        signalMapper -> setMapping (b8, 200) ;
        signalMapper -> setMapping (b9, 500) ;
        signalMapper -> setMapping (b10, 1000) ;
        connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(changeSumCash(int))) ;
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
        cashWidget->setLayout(layout);
        QGridLayout *layoutSet = new QGridLayout();
        QPushButton *s1 = new QPushButton("Turn Off");
        QString temp = "";
        temp += "Limit for cash ";
        temp += QString::number(limitCash);
        QPushButton *s3 = new QPushButton(temp);
        temp = "";
        temp += "Limit for cash insert ";
        temp += QString::number(limitCashInsert);
        QPushButton *s4 = new QPushButton(temp);
        QPushButton *s5 = new QPushButton("Exit");
        layoutSet->addWidget(s1);
        layoutSet->addWidget(s3);
        layoutSet->addWidget(s4);
        layoutSet->addWidget(s5);
        connect(s1, SIGNAL (clicked()), this, SLOT (s1()));
        connect(s3, SIGNAL (clicked()), this, SLOT (s3()));
        connect(s4, SIGNAL (clicked()), this, SLOT (s4()));
        connect(s5, SIGNAL (clicked()), this, SLOT (s5()));
        settingsWidget->setLayout(layoutSet);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::s1()
{
    if(working){
        QPushButton *q = qobject_cast<QPushButton*>(settingsWidget->children().at(1));
        turnOff();
        working = !working;
        q->setText("Turn On");
    } else {
        QPushButton *q = qobject_cast<QPushButton*>(settingsWidget->children().at(1));
        turnOn();
        working = !working;
        q->setText("Turn Off");
    }

}

void MainWindow::s3()
{
    int res = 0;
    do{
        res = QInputDialog::getInt(this, tr("New limit"),
                                   tr("Limit: "), QLineEdit::Normal);


    } while (res<0);
    if (res != 0){
        limitCash = res;
        QPushButton *q = qobject_cast<QPushButton*>(settingsWidget->children().at(2));
        QString temp = "";
        temp += "Limit for cash ";
        temp += QString::number(limitCash);
        q->setText(temp);
        QMessageBox::information(this, tr("Limit"),
                                 tr(temp.toUtf8().data()));
    }
}
void MainWindow::s4()
{
    int res = 0;
    do{
        res = QInputDialog::getInt(this, tr("New limit"),
                                   tr("Limit: "), QLineEdit::Normal);


    } while (res<0);
    if (res != 0){
        limitCashInsert = res;
        QPushButton *q = qobject_cast<QPushButton*>(settingsWidget->children().at(3));
        QString temp = "";
        temp += "Limit for cash insert ";
        temp += QString::number(limitCashInsert);
        q->setText(temp);
        QMessageBox::information(this, tr("Limit"),
                                 tr(temp.toUtf8().data()));
    }
}

void MainWindow::s5()
{
    settingsWidget->close();
    this->show();
}

void MainWindow::changeSumCash(const int a)
{
    ui->sum->setText(QString::number(ui->sum->text().toInt() + a));
    ui->addCash->setText("Current amount: " + ui->sum->text() + "\n1 Confirm");
    cashWidget->close();
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
        if(text.length() != 16 || text.toULongLong() == 0){
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
                    ui->pin->setText("");
                    ui->settingsBtn->setDisabled(true);
                    ui->empty->close();
                    ui->firstWindow->show();
                    ui->pins->setText("3");
                    ui->insertCard->setDisabled(true);
                    setButtonOn();

                    break;
                }

            }
        }

    } while (text.length() != 16 || text.toULongLong() == 0);



}

void MainWindow::on_screen1_clicked()
{

    if(!ui->mainWindow->isHidden()){
        QString temp ("Balance for current card is ");
        temp += QString::number(database.currentCard.getBalance());
        QMessageBox::information(this, tr("Balance"),
                                 tr(temp.toUtf8().data()));
    } else if(!ui->cards->isHidden()){
        checkBlockCard(0);

    } else if(!ui->cash->isHidden()){
        giveCash(50);
    } else if(!ui->addCash->isHidden()){
        giveCash(-(ui->sum->text().toInt()));
        ui->addCash->close();
        ui->mainWindow->show();
        ui->sum->setText("0");
        ui->insertCash->setDisabled(true);
    } else if(!ui->other->isHidden()){
        bool ok;
        int res;
        QString text;
        QRegExp rx("(\\+38)?0([0-9]{2}|\\([0-9]{2}\\))[0-9]{7}");
        do{
            text = QInputDialog::getText(this, tr("Insert phone number"),
                                         tr("Phone number: "), QLineEdit::Normal,
                                         "", &ok);
            if(!ok) return;

        } while (!rx.exactMatch(text));
        do{
            res = QInputDialog::getInt(this, tr("Choose amount"),
                                       tr("Amount: "), QLineEdit::Normal);


        } while (res<0);
        if(res != 0){

            QString temp ("Phone number ");
            temp += text;
            temp += " was replenished for ";
            temp += QString::number(res);
            QMessageBox::information(this, tr("Phone number replenished"),
                                     tr(temp.toUtf8().data()));
            database.getCash(database.currentCard.getNumber(), res);
        }

    }

}
void MainWindow::on_screen2_clicked()
{
    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->close();
        ui->cash->show();

    } else if(!ui->cards->isHidden()){

        checkBlockCard(1);

    } else if(!ui->cash->isHidden()){
        giveCash(100);
    } else if(!ui->other->isHidden()){
        int res;
        do{
            res = QInputDialog::getInt(this, tr("Choose amount"),
                                       tr("Amount: "), QLineEdit::Normal);


        } while (res<0);
        if(res != 0){

            QString temp ("You donated for a charity ");
            temp += QString::number(res);
            temp += ". Thank You!";

            QMessageBox::information(this, tr("Charity"),
                                     tr(temp.toUtf8().data()));
            database.getCash(database.currentCard.getNumber(), res);
        }

    }
}

void MainWindow::on_screen3_clicked()
{
    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->close();
        ui->addCash->show();

        ui->insertCash->setDisabled(false);
        ui->addCash->setText("Current amount: " + ui->sum->text() + "\n1 Confirm");


    } else if(!ui->cards->isHidden()){
        checkBlockCard(2);

    } else if(!ui->cash->isHidden()){
        giveCash(200);
    } else if(!ui->other->isHidden()){
        QString res ("");
        for(size_t i = 0; i<database.getTransactionAll().sizes(); ++i){
            if(database.getTransactionAll()[i].getRecipient() == database.currentCard.getNumber() ||
                    database.getTransactionAll()[i].getSender() == database.currentCard.getNumber() ){
                res += database.getTransactionAll()[i];
                res +="\n";
            }
        }
        if(res == ""){
            QMessageBox::information(this, tr("Extract"),
                                     tr("Extract is empty"));
        } else {
            QMessageBox::information(this, tr("Extract"),
                                     tr(res.toUtf8().data()));
        }


    }
}
void MainWindow::on_screen4_clicked()
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
            if(database.currentCard.getNumber() == card){
                QMessageBox::warning(this, tr("Error"),
                                     tr("You can not send money to the same card"));


            }

        } while (card.length() != 16 || card.toULongLong() == 0 || database.currentCard.getNumber() == card);
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
        checkBlockCard(3);

    } else if(!ui->cash->isHidden()){
        giveCash(500);
    }
}

void MainWindow::on_screen5_clicked()
{
    if(!ui->mainWindow->isHidden()){
        currentState = blockCard;
        ui->mainWindow->hide();
        setButtonOn();

        ui->firstWindow->setText("Enter PIN:");
         ui->pin->setText("");
        ui->firstWindow->show();


    } else if(!ui->cards->isHidden()){
        checkBlockCard(4);

    } else if(!ui->cash->isHidden()){
        giveCash(1000);
    }
}
void MainWindow::on_screen6_clicked()
{
    if(!ui->mainWindow->isHidden()){
        ui->mainWindow->hide();
        setButtonOn();
        currentState = changePIN;
        ui->firstWindow->setText("Enter old PIN:");
         ui->pin->setText("");
        ui->firstWindow->show();
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

        ui->mainWindow->close();
        ui->other->show();
    }
}
void MainWindow::on_screen8_clicked()
{
    if(!ui->mainWindow->isHidden()){

        setDefault();


    } else if(!ui->cards->isHidden()){
        ui->mainWindow->show();
        ui->cards->close();

    } else if(!ui->cash->isHidden()){
        ui->mainWindow->show();
        ui->cash->close();

    } else if(!ui->other->isHidden()){
        ui->mainWindow->show();
        ui->other->close();

    }
}

void MainWindow::on_b0_clicked()
{
    ui->firstWindow->setText(ui->firstWindow->toPlainText()+"*");
    ui->pin->setText(ui->pin->toPlainText() + "0");
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
{
    switch (currentState) {
    case unauthorized:
        if(!ui->firstWindow->isHidden()) {
            if( ui->pin->toPlainText() == database.currentCard.getPin()){
                QMessageBox::information(this, tr("Welcome"),
                                         tr("PIN is correct"));
                setButtonOff();

                ui->firstWindow->close();
                ui->mainWindow->show();

                ui->empty->close();
               currentState = authorized;
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
        break;
     case blockCard:
        if( ui->pin->toPlainText() == database.currentCard.getPin()){
            {
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
                    on_cancel_clicked();
                    break;
                default:
                    // should never be reached
                    break;
                }
            }
        } else {
            ui->firstWindow->setText("Enter PIN:");
             ui->pin->setText("");
            QMessageBox::warning(this, tr("Error"),
                                 tr("Wrong PIN"));

        }
        break;
     case changePIN:
        QStringList level = ui->pin->toPlainText().split(QLatin1Char('\n'), Qt::SkipEmptyParts);
        switch (level.size()) {
        case 1:
            if( ui->pin->toPlainText() == database.currentCard.getPin()){
                ui->firstWindow->setText(ui->firstWindow->toPlainText()+"\nEnter new PIN:");
                ui->pin->setText(ui->pin->toPlainText() +"\n");
            } else {
                ui->firstWindow->setText("Enter old PIN:");
                 ui->pin->setText("");
                QMessageBox::warning(this, tr("Error"),
                                     tr("Wrong PIN"));

            }
            break;
        case 2:
            if(level.at(1).size() != 4){
                on_reset_clicked();
                QMessageBox::warning(this, tr("Error"),
                                     tr("PIN must be 4 numbers"));
            } else if(level.at(1) == level.at(0)){
                on_reset_clicked();
                QMessageBox::warning(this, tr("Error"),
                                     tr("New PIN can not be as previous"));
            } else{
                ui->firstWindow->setText(ui->firstWindow->toPlainText()+"\nConfirm new PIN:");
                ui->pin->setText(ui->pin->toPlainText() +"\n");
            }

            break;
        case 3:
            if( level.at(1) == level.at(2)){
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
                   ui->pin->setText("");
                   ui->firstWindow->setText("Enter PIN:\n");
                   ui->firstWindow->hide();
                   setButtonOff();
                   ui->mainWindow->show();
                   database.changePin(database.currentCard.getNumber(), level.at(2));
                      QMessageBox::information(this, tr("Pin"),
                                                     tr("Pin in changed"));
                      currentState = authorized;

                     break;
                 case QMessageBox::Cancel:
                   ui->firstWindow->setText("Enter old PIN:");
                    ui->pin->setText("");
                     break;
                 default:
                     // should never be reached
                     break;
               }
            } else {
                on_reset_clicked();
                QMessageBox::warning(this, tr("Error"),
                                     tr("PIN do not matchs"));
            }
            break;
        default:
            break;
        }

        break;
    }


}
void MainWindow::on_reset_clicked()
{
    switch (currentState) {
    case unauthorized:
        if(!ui->firstWindow->isHidden()) {
            ui->pin->setText("");
            ui->firstWindow->setText("Enter PIN:\n");
        }
        break;
     case changePIN:
        ui->firstWindow->setText("Enter old PIN:");
         ui->pin->setText("");
        break;
     case blockCard:
        ui->firstWindow->setText("Enter PIN:");
         ui->pin->setText("");
        break;
    }
}

void MainWindow::on_cancel_clicked()
{
    switch (currentState) {
    case unauthorized:
        if(!ui->firstWindow->isHidden()) {
            ui->pin->setText("");
            ui->firstWindow->close();
            ui->mainWindow->close();
            ui->insertCard->setDisabled(false);
            setButtonOff();
            ui->empty->show();
        }
        break;
     case changePIN:
        ui->pin->setText("");
        ui->firstWindow->setText("Enter PIN:\n");
        ui->firstWindow->hide();
        setButtonOff();
        ui->mainWindow->show();
        currentState = authorized;
        break;
    case blockCard:
       ui->pin->setText("");
       ui->firstWindow->setText("Enter PIN:\n");
       ui->firstWindow->hide();
       setButtonOff();
       ui->mainWindow->show();
       currentState = authorized;
       break;
    }

}



void MainWindow::on_insertCash_clicked()
{
    cashWidget->show();
}

void MainWindow::setButtonOff()
{
    ui->b0->setDisabled(true);
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
    ui->b0->setDisabled(false);
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

void MainWindow::turnOff()
{
    ui->insertCard->setDisabled(true);
    ui->screen1->setDisabled(true);
    ui->screen2->setDisabled(true);
    ui->screen3->setDisabled(true);
    ui->screen4->setDisabled(true);
    ui->screen5->setDisabled(true);
    ui->screen6->setDisabled(true);
    ui->screen7->setDisabled(true);
    ui->screen8->setDisabled(true);

}

void MainWindow::turnOn()
{
    ui->insertCard->setDisabled(false);
    ui->screen1->setDisabled(false);
    ui->screen2->setDisabled(false);
    ui->screen3->setDisabled(false);
    ui->screen4->setDisabled(false);
    ui->screen5->setDisabled(false);
    ui->screen6->setDisabled(false);
    ui->screen7->setDisabled(false);
    ui->screen8->setDisabled(false);
}



void MainWindow::setDefault()
{
    ui->firstWindow->close();
    ui->mainWindow->close();
    ui->pin->close();
    ui->cash->close();
    ui->settingsBtn->setDisabled(false);
    ui->other->close();
    ui->cards->close();
    ui->addCash->close();
    ui->insertCash->setDisabled(true);
    ui->pin->close();
    ui->pins->close();
    ui->sum->close();
    ui->empty->show();
    ui->insertCard->setDisabled(false);
    ui->b0->setDisabled(true);
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
    currentState = unauthorized;
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
{   if(a < 0 && (-a) > limitCashInsert){
        QMessageBox::warning(this, tr("Error"),
                             tr("Limit is exceeded"));
    }else if(a > limitCash){
        QMessageBox::warning(this, tr("Error"),
                             tr("Limit is exceeded"));
    } else if (database.currentCard.getBalance() < a){
        QMessageBox::warning(this, tr("Error"),
                             tr("Not enough money"));
    } else {
        database.getCash(database.currentCard.getNumber(),a);
        if(a > 0){
            QString temp ("You got ");
            temp+=QString::number(a);
            temp+=" dollars";
            QMessageBox::information(this, tr("Cash"),
                                     tr(temp.toUtf8().data()));
        } else {

            QString temp ("Balance for current card is ");
            temp += QString::number(database.currentCard.getBalance());;
            QMessageBox::information(this, tr("Balance"),
                                     tr(temp.toUtf8().data()));
        }

    }
}



void MainWindow::on_settingsBtn_clicked()
{
    settingsWidget->show();

}



