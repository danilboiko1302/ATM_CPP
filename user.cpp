#include "user.h"

const Sequence<Card>& User::getCards() const
{
    return cards;
}

const QString User::getName() const
{
    return name;
}

User &User::addCard(const Card& a)
{
    cards.add(a);
    return *this;
}


User:: User():  cards(), name ()
{

}
User:: User(const char* a):  cards(), name (a)
{

}

User:: User(const User & a):  cards(), name (a.getName())
{
    for(size_t i = 0; i< a.getCards().sizes(); i++){
        cards.add(a.cards[i]);
    }
}


User &User::operator=(const User & user)
{
    this->name = user.getName();
    for(size_t i =0; i<user.cards.sizes(); i++){
        this->cards.add(user.cards[i]);
    }
    return *this;
}

void User::blockCard(const char * a)
{
    blockCard(*(new QString(a)));
}
void User::blockCard(const QString& a)
{
    for(size_t j =0; j < cards.sizes(); j++){
        if( cards[j].getNumber() == a){
            cards[j].setStatus("block");
        }
    }
}
void User::unblockCard(const char * a)
{
    unblockCard(*(new QString(a)));
}
void User::unblockCard(const QString& a)
{
    for(size_t j =0; j < cards.sizes(); j++){
        if( cards[j].getNumber() == a){
            cards[j].setStatus("active");
        }
    }
}
ostream &operator<<(ostream &os, const User &user) {

    os<<"User: "<< user.getName().toUtf8().data() <<endl;
    for(size_t i=0; i<user.getCards().sizes(); i++) {
        os<<"Card: "<< user.getCards()[i]<<endl;
    }
    os<<'.';
    return os;
}
