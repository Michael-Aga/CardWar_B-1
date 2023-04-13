#include "card.hpp"

using namespace std;
using namespace ariel;

void Card::setMyShape(const shape &freshShape)
{
    this->myShape = freshShape;
}

Card::shape Card::getMyShape() const
{
    return this->myShape;
}

string Card::getShapeString()
{
    if ((int)this->getMyShape() == 0)
    {
        return "clubs";
    }
    if ((int)this->getMyShape() == 1)
    {
        return "diamonds";
    }
    if ((int)this->getMyShape() == 2)
    {
        return "hearts";
    }
    if ((int)this->getMyShape() == 3)
    {
        return "spades";
    }

    return "Sorry doesnt match try again !";
};

void Card::setMyValue(const value &freshValue)
{
    this->myValue = freshValue;
}

Card::value Card::getMyValue() const
{
    return this->myValue;
}

string Card::getValueString()
{
    if ((int)this->getMyValue() == 2)
    {
        return "two";
    }
    if ((int)this->getMyValue() == 3)
    {
        return "three";
    }
    if ((int)this->getMyValue() == 4)
    {
        return "four";
    }
    if ((int)this->getMyValue() == 5)
    {
        return "five";
    }
    if ((int)this->getMyValue() == 6)
    {
        return "six";
    }
    if ((int)this->getMyValue() == 7)
    {
        return "seven";
    }
    if ((int)this->getMyValue() == 8)
    {
        return "eight";
    }
    if ((int)this->getMyValue() == 9)
    {
        return "nine";
    }
    if ((int)this->getMyValue() == 10)
    {
        return "ten";
    }
    if ((int)this->getMyValue() == 11)
    {
        return "Jack";
    }
    if ((int)this->getMyValue() == 12)
    {
        return "Queen";
    }
    if ((int)this->getMyValue() == 13)
    {
        return "King";
    }
    if ((int)this->getMyValue() == 14)
    {
        return "Ace";
    }

    return "Sorry doesnt match try again !";
};