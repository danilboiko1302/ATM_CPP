#ifndef USER_H
#define USER_H
#include <QApplication>
#include "Sequence.h"
#include "card.h"
class User
{
private:
    Sequence <Card> cards;
    QString name;
public:
    User(const char*);
};

#endif // USER_H
