#include "game.hpp"

using namespace std;
using namespace ariel;

Game::Game(Player &player1, Player &player2) : firstPlayer(player1), secondPlayer(player2)
{
    createGameDeck();

    srand(time(0));
    random_shuffle((this->gameDeck.begin()), (this->gameDeck.end()));

    distributeTheCards();
};

void Game::createGameDeck()
{
    for (int i = Card::clubs; i != Card::lastShape; i++)
    {
        for (int j = Card::two; j != Card::lastValue; j++)
        {
            this->gameDeck.push_back(Card((Card::shape)i, (Card::value)j));
        }
    }
};

void Game::distributeTheCards()
{
    for (int currentCard = this->gameDeck.size(); currentCard > 0; currentCard--)
    {
        if (currentCard > 26)
        {
            this->firstPlayer.getMyCards().push_back(this->gameDeck[(size_t)currentCard]);
            this->gameDeck.pop_back();
        }

        if (currentCard <= 26)
        {
            this->secondPlayer.getMyCards().push_back(this->gameDeck[(size_t)currentCard]);
            this->gameDeck.pop_back();
        }
    }
};

void Game::logTurn()
{
    this->didYouSetLog = 0;
    string firstName = this->firstPlayer.getMyName();
    string firstCardShape = this->firstPlayer.getMyCards().back().getShapeString();
    string firstCardValue = this->firstPlayer.getMyCards().back().getValueString();
    Card::value firstCardRealValue = this->firstPlayer.getMyCards().back().getMyValue();

    string secondName = this->secondPlayer.getMyName();
    string secondCardShape = this->secondPlayer.getMyCards().back().getShapeString();
    string secondCardValue = this->secondPlayer.getMyCards().back().getValueString();
    Card::value secondCardRealValue = this->secondPlayer.getMyCards().back().getMyValue();

    if (firstCardRealValue == secondCardRealValue)
    {
        this->gameLog.push_back(firstName + " played " + firstCardValue + " of " + firstCardShape + " " +
                                secondName + " played " + secondCardValue + " of " + secondCardShape + ". " + "draw.");
    }

    if (firstCardRealValue == 2 && secondCardRealValue == 14)
    {
        this->gameLog.push_back(firstName + " played " + firstCardValue + " of " + firstCardShape + " " +
                                secondName + " played " + secondCardValue + " of " + secondCardShape + ". " + firstName + " wins.");
        this->didYouSetLog = 1;
    }

    if (firstCardRealValue == 14 && secondCardRealValue == 2)
    {
        this->gameLog.push_back(firstName + " played " + firstCardValue + " of " + firstCardShape + " " +
                                secondName + " played " + secondCardValue + " of " + secondCardShape + ". " + secondName + " wins.");
        this->didYouSetLog = 1;
    }

    if (firstCardRealValue > secondCardRealValue && this->didYouSetLog == 0)
    {
        this->gameLog.push_back(firstName + " played " + firstCardValue + " of " + firstCardShape + " " +
                                secondName + " played " + secondCardValue + " of " + secondCardShape + ". " + firstName + " wins.");
    }

    if (firstCardRealValue < secondCardRealValue && this->didYouSetLog == 0)
    {
        this->gameLog.push_back(firstName + " played " + firstCardValue + " of " + firstCardShape + " " +
                                secondName + " played " + secondCardValue + " of " + secondCardShape + ". " + secondName + " wins.");
    }
};

void Game::checkValidTurn()
{
    if (this->firstPlayer.getMyCards().size() == 0 || this->secondPlayer.getMyCards().size() == 0)
    {
        throw std::invalid_argument("The game is over ! you cant keep playing ! ");
    }

    if (this->firstPlayer.getMyCards().back().getMyShape() == this->secondPlayer.getMyCards().back().getMyShape() &&
        this->firstPlayer.getMyCards().back().getMyValue() == this->secondPlayer.getMyCards().back().getMyValue())
    {
        throw std::invalid_argument("You cant play with yourself here ! ");
    }
}

void Game::playTurn()
{
    this->gameLogEquals = 0;
    this->turnsPlayed++;
    this->didYouSetWinner = 0;
    logTurn();
    checkValidTurn();

    Card::value firstPlayerCardValue = this->firstPlayer.getMyCards().back().getMyValue();
    Card::value secondPlayerCardValue = this->secondPlayer.getMyCards().back().getMyValue();
    vector<Card> winningPot;

    while (firstPlayerCardValue == secondPlayerCardValue)
    {
        this->gameLogEquals++;
        this->drawCount++;
        if (this->firstPlayer.stacksize() == 0 && this->secondPlayer.stacksize() == 0 &&
            firstPlayerCardValue == secondPlayerCardValue)
        {
            const size_t mySize = winningPot.size() / 2;
            for (int currentCard = winningPot.size(); currentCard > 0; currentCard--)
            {
                if (currentCard > mySize)
                {
                    this->firstPlayer.getMyWinnings().push_back(this->gameDeck[(size_t)currentCard]);
                    winningPot.pop_back();
                }

                if (currentCard <= mySize)
                {
                    this->secondPlayer.getMyCards().push_back(this->gameDeck[(size_t)currentCard]);
                    winningPot.pop_back();
                }
            }
        }
        this->turnsPlayed++;

        winningPot.push_back(this->firstPlayer.getMyCards().back());
        winningPot.push_back(this->secondPlayer.getMyCards().back());

        this->firstPlayer.getMyCards().pop_back();
        this->secondPlayer.getMyCards().pop_back();

        firstPlayerCardValue = this->firstPlayer.getMyCards().back().getMyValue();
        secondPlayerCardValue = this->secondPlayer.getMyCards().back().getMyValue();

        logTurn();
    }

    if (firstPlayerCardValue == 2 && secondPlayerCardValue == 14)
    {
        this->didYouSetWinner = 1;

        winningPot.push_back(this->firstPlayer.getMyCards().back());
        winningPot.push_back(this->secondPlayer.getMyCards().back());

        this->firstPlayer.getMyCards().pop_back();
        this->secondPlayer.getMyCards().pop_back();

        for (int currentCard = (winningPot.size() - 1); currentCard >= 0; currentCard--)
        {
            this->firstPlayer.getMyWinnings().push_back(winningPot[(size_t)currentCard]);
            winningPot.pop_back();
        }
    }

    if (firstPlayerCardValue == 14 && secondPlayerCardValue == 2)
    {
        this->didYouSetWinner = 1;

        winningPot.push_back(this->firstPlayer.getMyCards().back());
        winningPot.push_back(this->secondPlayer.getMyCards().back());

        this->firstPlayer.getMyCards().pop_back();
        this->secondPlayer.getMyCards().pop_back();

        for (int currentCard = (winningPot.size() - 1); currentCard >= 0; currentCard--)
        {
            this->secondPlayer.getMyWinnings().push_back(winningPot[(size_t)currentCard]);
            winningPot.pop_back();
        }
    }

    if ((firstPlayerCardValue > secondPlayerCardValue) && this->didYouSetWinner == 0)
    {
        winningPot.push_back(this->firstPlayer.getMyCards().back());
        winningPot.push_back(this->secondPlayer.getMyCards().back());

        this->firstPlayer.getMyCards().pop_back();
        this->secondPlayer.getMyCards().pop_back();

        for (int currentCard = (winningPot.size() - 1); currentCard >= 0; currentCard--)
        {
            this->firstPlayer.getMyWinnings().push_back(winningPot[(size_t)currentCard]);
            winningPot.pop_back();
        }
    }

    if ((firstPlayerCardValue < secondPlayerCardValue) && this->didYouSetWinner == 0)
    {
        winningPot.push_back(this->firstPlayer.getMyCards().back());
        winningPot.push_back(this->secondPlayer.getMyCards().back());

        this->firstPlayer.getMyCards().pop_back();
        this->secondPlayer.getMyCards().pop_back();

        for (int currentCard = (winningPot.size() - 1); currentCard >= 0; currentCard--)
        {
            this->secondPlayer.getMyWinnings().push_back(winningPot[(size_t)currentCard]);
            winningPot.pop_back();
        }
    }
};

void Game::printLastTurn()
{
    if (this->gameLogEquals > 0)
    {
        for (size_t i = 0; i < this->gameLog.size() ; i--)
        {
            cout << this->gameLog.at(this->gameLog.size() - i) << " ";
        }
        this->gameLogEquals = 0;
    }

    else
    {
        cout << this->gameLog.back() << endl;
    }
};

void Game::playAll()
{
    while (this->firstPlayer.stacksize() > 0 || this->secondPlayer.stacksize() > 0)
    {
        playTurn();
    }
};

void Game::printWiner()
{
    if (this->firstPlayer.cardesTaken() > this->secondPlayer.cardesTaken())
    {
        cout << "The winner is : " << this->firstPlayer.getMyName() << endl;
    }

    if (this->firstPlayer.cardesTaken() < this->secondPlayer.cardesTaken())
    {
        cout << "The winner is : " << this->secondPlayer.getMyName() << endl;
    }

    if (this->firstPlayer.cardesTaken() == this->secondPlayer.cardesTaken())
    {
        cout << "Everyone is a winner ! (There is a tie ...)" << endl;
    }
};

void Game::printLog()
{
    for (size_t i = 0; i < this->gameLog.size(); i++)
    {
        cout << this->gameLog[i] << endl;
    }
};

void Game::printStats()
{

    cout << this->firstPlayer.getMyName();
    cout << " Win rate : " << (this->firstPlayer.cardesTaken() / this->turnsPlayed) * 50 << "%";
    cout << " cards won : " << this->firstPlayer.cardesTaken() << endl;

    cout << this->secondPlayer.getMyName();
    cout << " Win rate : " << (this->secondPlayer.cardesTaken() / this->turnsPlayed) * 50 << "%";
    cout << " cards won : " << this->secondPlayer.cardesTaken() << endl;

    cout << "Draw rate : " << (this->drawCount / this->turnsPlayed) * 100 << "%";
    cout << " Amount of draws that happend : " << this->drawCount << endl;
};