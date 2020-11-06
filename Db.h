
#ifndef DB_H
#define DB_H
#include <QtSql>
#include "user.h"
class Db{
private:
    int amountUser = -1;
    int amountCard = -1;
    int amountTransaction = -1;
    User currentUser;
    Sequence <User> users;
    Sequence <Transaction> transactions;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
public:
    bool addUser(const char*);
    bool addCard(const char*,const char*,const char*,const int,const char*,const int);
    bool addTransaction(const char*);
    Sequence <User>& getUserAll();
    Sequence <Card>& getCardAll();
    Sequence <Transaction>& getTransactionAll();
    Db(const char*,const char*,const char*,const char*);
    User getCurrentUser() const;
    void setCurrentUser(const User &value);
};

#endif // DB_H
