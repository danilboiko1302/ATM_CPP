#include "Db.h"

//User Db::getCurrentUser() const
//{
//    return currentUser;
//}

//void Db::setCurrentUser(const User value)
//{
//    currentUser = value;
//}

//Card Db::getCurrentCard() const
//{
//    return currentCard;
//}

//void Db::setCurrentCard(const Card value)
//{
//    currentCard = value;
//}

void Db::backUp()
{
    QSqlQuery a_query;
    QString str = "DROP TABLE user;";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
         qDebug() <<"DROP TABLE user;";
    }
    str = "DROP TABLE card;";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
         qDebug() <<"DROP TABLE card;";
    }
    str = "DROP TABLE trans;";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
          qDebug() <<"DROP TABLE trans;";
    }
    str = "CREATE TABLE user ("
                    "iduser integer PRIMARY KEY NOT NULL, "
                    "name VARCHAR(255) UNIQUE"
                    ");";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();

         qDebug() <<"CREATE TABLE users;";
    }
    str = "CREATE TABLE card ("
                    "idcard integer PRIMARY KEY NOT NULL, "
                    "number VARCHAR(45) NOT NULL UNIQUE, "
                    "pin VARCHAR(45) NOT NULL, "
                    "type VARCHAR(45) NOT NULL, "
                    "balance integer NOT NULL, "
                    "status VARCHAR(45) NOT NULL, "
                    "user integer NOT NULL"
                    ");";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
    }
    str = "CREATE TABLE trans ("
                    "idtransaction integer PRIMARY KEY NOT NULL, "
                    "datetime DATETIME NOT NULL, "
                    "status VARCHAR(255) NOT NULL, "
                    "amount integer NOT NULL, "
                    "senderCard VARCHAR(45) NOT NULL, "
                    "recipientCard VARCHAR(45) NOT NULL"
                    ");";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
    }
    str = "INSERT INTO user VALUES (1, 'Danya');";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
    }
    str = "INSERT INTO user VALUES (2, 'Andreyw');";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
    }
    str = "INSERT INTO card VALUES (1, '4144785936257485', '1234', 'debit', 1000, 'active', 1);";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
    }
    str = "INSERT INTO card VALUES (2, '4144785936257478', '3636', 'debit', 1000, 'active', 1);";
    if(!a_query.exec(str)){
         qDebug() <<a_query.lastError();
    }

}

bool Db::addUser(const char * a)
{
    char str1[11];
    sprintf(str1, "%d", users.sizes()+1);
    QSqlQuery a_query;
    QString str_insert = "INSERT INTO user (iduser, name) "
                   "VALUES (%1, '%2');";
        QString   str = str_insert.arg(str1)
                   .arg(a);
        bool res = a_query.exec(str);
        if(res){
            users.add(*(new User(a)));
        }
        qDebug() <<a_query.lastError();

        return  res;

}

bool Db::addCard(const char * number, const char * pin, const char * type, const int balance, const char * status, const int userid)
{
    char id[11];
      sprintf(id, "%d", getCardAll().sizes()+1);
      char user[11];
        sprintf(user, "%d",userid);
        char bal[11];
          sprintf(bal, "%d",balance);
    QSqlQuery a_query;
   QString str_insert = "INSERT INTO card VALUES (%1, '%2', '%3', '%4', %5, '%6', %7);";
       QString   str = str_insert.arg(id)
                  .arg(number)
                  .arg(pin)
                  .arg(type)
                  .arg(bal)
                  .arg(status)
                  .arg(user);
       bool res = a_query.exec(str);

       qDebug() <<a_query.lastError();

       return  res;

}

Sequence<User> &Db::getUserAll()
{
    return users;
}

Sequence<Card> &Db::getCardAll()
{
    Sequence<Card> * res = new Sequence<Card>();
    for(size_t i =0; i < users.sizes(); i++){
        for(size_t j =0; j < users[i].getCards().sizes(); j++){
            res->add(users[i].getCards()[j]);
        }
    }
    return *res;
}

Sequence<Transaction> &Db::getTransactionAll()
{

}

Db::Db(const char* host,const char* schema,const char* user,const char* password){
    db.setHostName(host);
    db.setDatabaseName(schema);
    db.setUserName(user);
    db.setPassword(password);
    db.open();
    //backUp();
     QSqlQuery a_query;
    if (!a_query.exec("SELECT * FROM user")) {
        qDebug() << "Даже селект не получается, я пас.";
       // return -2;
    }
    while (a_query.next()) {
        users.add(*(new User(a_query.value(1).toString().toUtf8().data())));
         qDebug()<<a_query.value(1).toString();
       // qDebug() << a_query.value(0).toInt();
    }
    if (!a_query.exec("SELECT * FROM card")) {
        qDebug() << "Даже селект не получается, я пас.";
       // return -2;
    }
    while (a_query.next()) {
        QString number = a_query.value(1).toString();
        QString pin= a_query.value(2).toString();
        QString type = a_query.value(3).toString();


        int balance = a_query.value(4).toInt();
         QString status = a_query.value(5).toString();
        int userid = a_query.value(6).toInt();
        Card res (number, pin, type, balance,status,userid);
        users[userid-1].addCard(res);

         cout<<res<<endl;
    }

}

void Db::blockCard(const char * a)
{
    blockCard(*(new QString(a)));
}

void Db::blockCard(const QString & a)
{

    QSqlQuery a_query;
    QString str_insert = "UPDATE  card  SET status='block' WHERE number='%1';";
        QString   str = str_insert.arg(a);
        bool res = a_query.exec(str);
       if(res){
           for(size_t i =0; i < users.sizes(); i++){
               for(size_t j =0; j < users[i].getCards().sizes(); j++){
                   if(users[i].getCards()[j].getNumber() == a){
                       users[i].blockCard(a);
                   }
               }
           }

       }
        qDebug() <<a_query.lastError();


}

void Db::changePin(const QString & name, const QString & pin)
{
    QSqlQuery a_query;
    QString str_insert = "UPDATE  card  SET pin='%1' WHERE number='%2';";
        QString   str = str_insert.arg(pin).arg(name);
        bool res = a_query.exec(str);
       if(res){
           for(size_t i =0; i < users.sizes(); i++){
               for(size_t j =0; j < users[i].getCards().sizes(); j++){
                   if(users[i].getCards()[j].getNumber() == name){
                       users[i].changePin(name, pin);
                   }
               }
           }

       }
        qDebug() <<a_query.lastError();
}

void Db::unblockCard(const char * a)
{
    unblockCard(*(new QString(a)));
}

void Db::unblockCard(const QString & a)
{
    QSqlQuery a_query;
    QString str_insert = "UPDATE  card  SET status='active' WHERE number='%1';";
        QString   str = str_insert.arg(a);
        bool res = a_query.exec(str);
       if(res){
           for(size_t i =0; i < users.sizes(); i++){
               for(size_t j =0; j < users[i].getCards().sizes(); j++){
                   if(users[i].getCards()[j].getNumber() == a){
                       users[i].unblockCard(a);
                   }
               }
           }

       }
       qDebug() <<a_query.lastError();
}

void Db::getCash(const int a)
{
    char balance[11];
    sprintf(balance, "%d", currentCard.getBalance() - a);
    qDebug() <<balance;
    QSqlQuery a_query;
    QString str_insert = "UPDATE  card  SET balance=%1 WHERE number='%2';";
        QString   str = str_insert.arg(balance).arg(currentCard.getNumber());
        bool res = a_query.exec(str);
       if(res){
             currentCard.setBalance(currentCard.getBalance() - a);
             for(size_t i =0; i < users.sizes(); i++){
                 for(size_t j =0; j < users[i].getCards().sizes(); j++){
                     if(users[i].getCards()[j].getNumber() == currentCard.getNumber()){
                         users[i].getCash(currentCard.getNumber(),a);
                     }
                 }
             }

       }
       qDebug() <<a_query.lastError();

       getCardAll().show();
}
