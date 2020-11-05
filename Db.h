#include <QtSql>
#ifndef DB_H
#define DB_H
class Db{
private:
   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
public:
    char* check();
    Db(const char*,const char*,const char*,const char*);
};

#endif // DB_H
