#include "user.h"

const Sequence<Card>& User::getCards() const
{
    return cards;
}

const QString User::getName() const
{
    return name;
}


User:: User(const char* a):  cards(), name (a)
{

}

ostream &operator<<(ostream &os, const User &user) {

    os<<"User: "<< user.getName().toUtf8().data() <<endl;
    for(size_t i=0; i<user.getCards().sizes(); i++) {
        os<<"Card: "<< user.getCards()[i];
    }
    os<<'.';
    return os;
}
