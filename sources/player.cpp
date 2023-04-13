#include "player.hpp"

using namespace std;
using namespace ariel;

size_t Player::stacksize()
{
    return this->myCards.size();
};

size_t Player::cardesTaken()
{
    return this->myWinnings.size();
};

string Player::getMyName()
{
    return this->myName;
};

vector<Card> &Player::getMyCards()
{
    return this->myCards;
};

vector<Card> &Player::getMyWinnings()
{
    return this->myWinnings;
};