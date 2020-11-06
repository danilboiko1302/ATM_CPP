#include <QtSql>
#ifndef DB_H
#define DB_H
class Db{
    int amount = -1;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
public:
    bool addUser(const char*);
    bool addCard();
    bool addTransaction();
    Db(const char*,const char*,const char*,const char*);
};

#endif // DB_H
