#include "Player.h"

Player::Player(int playerNumber) :ID(playerNumber),alive(1), remainDices(0)
{
}


Player::~Player()
{
}

void Player::AddLand(Land& theLand)
{
    lands.insert(theLand);
}
void Player::DeleteLand(Land& theLand)
{
    lands.erase(theLand);
}