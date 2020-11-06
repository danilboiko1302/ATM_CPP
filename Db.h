#include <QtSql>
#include "user.h"
#ifndef DB_H
#define DB_H
class Db{

    int amountUser = -1;
    int amountCard = -1;
    int amountTransaction = -1;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
public:
    bool addUser(const char*);
    bool addCard(const char*);
    bool addTransaction(const char*);
    Sequence <User>& getUserAll();
    Sequence <Card>& getCardAll();
    Sequence <Transaction>& getTransactionAll();
    Db(const char*,const char*,const char*,const char*);
};

#endif // DB_H
