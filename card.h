#ifndef CARD_H
#define CARD_H
#include "Sequence.h"
#include <QApplication>
class Card
{
private:
    QString number;
    QString pin;
    QString type;
    int balance;
    QString status;
    int userid;
public:
    Card(const QString& ,const QString& ,const QString& ,const int,const QString& ,const int);
    Card(const char*,const char*,const char*,const int,const char*,const int);
    Card();
    Card(const Card&);
     Card& operator=(const Card&);
    QString& toString();
    QString getNumber() const;
    void setNumber(const QString &value);
    QString getPin() const;
    void setPin(const QString &value);
    QString getType() const;
    void setType(const QString &value);
    int getBalance() const;
    void setBalance(int value);
    QString getStatus() const;
    void setStatus(const QString &value);
    int getUserid() const;
    void setUserid(int value);
};
 ostream& operator<<(ostream& os, const Card& user);
#endif // CARD_H
