#include "transaction.h"

QString Transaction::getDatetime() const
{
    return datetime;
}

void Transaction::setDatetime(const QString &value)
{
    datetime = value;
}

int Transaction::getAmount() const
{
    return amount;
}

void Transaction::setAmount(int value)
{
    amount = value;
}

QString Transaction::getSender() const
{
    return sender;
}

void Transaction::setSender(const QString &value)
{
    sender = value;
}

QString Transaction::getRecipient() const
{
    return recipient;
}

void Transaction::setRecipient(const QString &value)
{
    recipient = value;
}

Transaction::Transaction()
{

}

Transaction::Transaction(const QString & datetime, const int amount, const QString & sender, const QString & recipient)
{
    this->datetime = datetime;
    this->amount = amount;
    this->sender = sender;
    this->recipient = recipient;
}

Transaction::Transaction(const Transaction & a)
{
    this->datetime = a.datetime;
    this->amount = a.amount;
    this->sender = a.sender;
    this->recipient = a.recipient;
}

Transaction &Transaction::operator=(const Transaction & a)
{
    this->datetime = a.datetime;
    this->amount = a.amount;
    this->sender = a.sender;
    this->recipient = a.recipient;
    return *this;
}
