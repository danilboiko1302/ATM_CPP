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

Card::Card()
{
    
}

ostream &operator<<(ostream &os, const Card &user)
{

   return os;
}
