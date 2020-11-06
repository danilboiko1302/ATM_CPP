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
