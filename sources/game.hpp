#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <random>
#include "player.hpp"
#include "card.hpp"

namespace ariel
{
    class Game
    {
    private:
        std::vector<std::string> gameLog;
        std::size_t gameLogEquals = 0;
        std::vector<Card> gameDeck;
        std::string myLastTurn;
        Player &firstPlayer;
        Player &secondPlayer;
        int didYouSetLog = 0;
        int didYouSetWinner = 0;
        double drawCount = 0;
        double turnsPlayed = 0;


    public:
        Game(ariel::Player &player1, ariel::Player &player2);

        void createGameDeck();
        void distributeTheCards();
        void checkValidTurn();
        void logTurn();

        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}
