#include "Db.h"

bool Db::addUser(const char * a)
{
     QSqlQuery a_query;
    QString str_insert = "INSERT INTO user (iduser, name) "
                   "VALUES (%1, '%2');";
        QString   str = str_insert.arg("4")
                   .arg("twwest");
        return  a_query.exec(str);

}

Sequence<User> &Db::getUserAll()
{

}

Sequence<Card> &Db::getCardAll()
{

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


    int number = 0;


    while (a_query.next()) {
      number++;
    }
    amountUser = number;
}
