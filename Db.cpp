#include "Db.h"

User Db::getCurrentUser() const
{
    return currentUser;
}

void Db::setCurrentUser(const User &value)
{
    currentUser = value;
}

Card Db::getCurrentCard() const
{
    return currentCard;
}

void Db::setCurrentCard(const Card &value)
{
    currentCard = value;
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
     QSqlQuery a_query;
    if (!a_query.exec("SELECT * FROM user")) {
        qDebug() << "Даже селект не получается, я пас.";
       // return -2;
    }
    while (a_query.next()) {
        users.add(*(new User(a_query.value(1).toString().toUtf8().data())));
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
         cout<<a_query.value(0).toInt()<<endl;
         cout<<res<<endl;
    }

}
