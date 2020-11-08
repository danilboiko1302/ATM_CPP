#include "card.h"



QString Card::getNumber() const
{
    return number;
}

void Card::setNumber(const QString &value)
{
    number = value;
}

QString Card::getPin() const
{
    return pin;
}

void Card::setPin(const QString &value)
{
    pin = value;
}

QString Card::getType() const
{
    return type;
}

void Card::setType(const QString &value)
{
    type = value;
}

int Card::getBalance() const
{
    return balance;
}

void Card::setBalance(int value)
{
    balance = value;
}

QString Card::getStatus() const
{
    return status;
}

void Card::setStatus(const QString &value)
{
    status = value;
}

int Card::getUserid() const
{
    return userid;
}

void Card::setUserid(int value)
{
    userid = value;
}

void Card::getCash(const int)
{

}

Card::Card(const QString & number, const QString & pin, const QString & type, const int balance, const QString & status, const int userid)
{
    this->number = number;
    this->pin = pin;
    this->type = type;
    this->balance = balance;
    this->status = status;
    this->userid = userid;
}

Card::Card(const char * number, const char * pin, const char * type, const int balance, const char * status, const int userid)
{
    this->number = number;
    this->pin = pin;
    this->type = type;
    this->balance = balance;
    this->status = status;
    this->userid = userid;
}

Card::Card()
{
    
}

Card::Card(const Card & a)
{
    this->number = a.number;
    this->pin = a.pin;
    this->type = a.type;
    this->balance = a.balance;
    this->status = a.status;
    this->userid = a.userid;

}

Card &Card::operator=(const Card & a)
{
    this->number = a.number;
    this->pin = a.pin;
    this->type = a.type;
    this->balance = a.balance;
    this->status = a.status;
    this->userid = a.userid;
    return *this;
}

ostream &operator<<(ostream &os, const Card & card)
{
    os<<"Card: number "<<card.getNumber().toUtf8().data();
    os<<" pin "<<card.getPin().toUtf8().data();
    os<<" type "<<card.getType().toUtf8().data();
    os<<" balance "<<card.getBalance();
    os<<" status "<<card.getStatus().toUtf8().data();
    os<<" userid "<<card.getUserid();
   return os;
}
