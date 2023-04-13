#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "card.hpp"

namespace ariel
{
    class Player
    {
    private:
        std::string myName;
        std::vector<Card> myCards;
        std::vector<Card> myWinnings;

    public:
        Player(const std::string &assignName) : myName(assignName){};

        std::size_t stacksize();
        std::size_t cardesTaken();

        std::string getMyName();
        std::vector<Card> &getMyCards();
        std::vector<Card> &getMyWinnings();
    };
}