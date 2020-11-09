
#ifndef DB_H
#define DB_H
#include <QtSql>
#include "user.h"
class Db{
private:


    Sequence <User> users;
    Sequence <Transaction> transactions;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

public:
    void backUp();
    User currentUser;
    Card currentCard;
    bool addUser(const char*);
    bool addCard(const char*,const char*,const char*,const int,const char*,const int);
    bool addTransaction(const char*);
    Sequence <User>& getUserAll();
    Sequence <Card>& getCardAll();
    Sequence <Transaction>& getTransactionAll();
    Db(const char*,const char*,const char*,const char*);
    void blockCard (const char* );
    void blockCard (const QString& );
    void changePin (const QString&,const QString& );
    void unblockCard (const char* );
    void unblockCard (const QString& );
    void getCash(const int);
//    User getCurrentUser() const;
//    void setCurrentUser(const User value);
//    Card getCurrentCard() const;
//    void setCurrentCard(const Card value);

};

#endif // DB_H
