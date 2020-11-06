#include "card.h"

QString Card::getName() const
{
    return name;
}

void Card::setName(const QString &value)
{
    name = value;
}

Card::Card()
{
    
}
