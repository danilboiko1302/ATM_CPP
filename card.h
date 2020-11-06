#ifndef CARD_H
#define CARD_H
#include "Sequence.h"
#include <QApplication>
class Card
{
public:
    Card();
};
ostream& operator<<(ostream& os, const Card& card) {

    os<<"123";
    return os;
}
#endif // CARD_H
