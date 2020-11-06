#ifndef USER_H
#define USER_H
#include <QApplication>
#include "Sequence.h"
#include "card.h"
#include "transaction.h"
class User
{
private:
    Sequence <Card> cards;
    QString name;
public:
   const Sequence <Card>& getCards() const;
    const QString getName() const;
    User(const char*);
};
ostream& operator<<(ostream& os, const User& user) {

    os<<"User: "<< user.getName().toUtf8().data() <<endl;
    for(size_t i=0; i<user.getCards().sizes(); i++) {
        os<<"Card: "<< user.getCards()[i];
    }
    os<<'.';
    return os;
}
#endif // USER_H
