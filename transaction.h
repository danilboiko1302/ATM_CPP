#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QApplication>

class Transaction
{
private:
    QString datetime;
    int amount;
    QString sender;
    QString recipient;
public:
    Transaction();
    Transaction(const QString&, const int, const QString&,const QString&);
    Transaction(const Transaction&);
    Transaction& operator=(const Transaction&);
    QString getDatetime() const;
    void setDatetime(const QString &value);
    int getAmount() const;
    void setAmount(int value);
    QString getSender() const;
    void setSender(const QString &value);
    QString getRecipient() const;
    void setRecipient(const QString &value);
};

#endif // TRANSACTION_H
