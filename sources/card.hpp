#pragma once
#include <stdio.h>
#include <string>

namespace ariel
{
    class Card
    {
    public:
            enum shape : unsigned char//Each card has a shape 
        {
            clubs,    //(♣)
            diamonds, //(♦)
            hearts,   //(♥)
            spades,    //(♠)
            lastShape
        };
        
        enum value : unsigned char//Each card has a name or value if you want
        {
            two = 2,
            three,
            four,
            five,
            six,
            seven,
            eight,
            nine,
            ten,
            Jack,
            Queen,
            King,
            Ace,
            lastValue
        };

    private:    
        shape myShape;
        value myValue;
    public:    
        Card(shape assignShape, value assignValue) :
        myShape(assignShape), myValue(assignValue) {};

        void setMyShape(const shape &freshShape);

        shape getMyShape() const;
        std::string getShapeString();

        void setMyValue(const value &freshValue);

        value getMyValue() const;
        std::string getValueString();
    };
};