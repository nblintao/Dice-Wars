#include "player.h"
#include<iostream>

Player::Player(int playerNumber) :ID(playerNumber),alive(1), remainDices(0)
{
}


Player::~Player()
{
}

void Player::AddLand(Land *theLand)
{
    lands.insert(theLand);
    this->AdjustMaxAdjacentLands();
}

void Player::DeleteLand(Land *theLand)
{
    lands.erase(theLand);
    if (this->lands.empty()) {
        this->Die();
    }
    this->AdjustMaxAdjacentLands();
}
void Player::Die()
{
    std::cout << "player" << this->ID << "die" << endl;
    this->alive = 0;
}
void Player::AdjustMaxAdjacentLands()
{
    int maxAdjacentLands = 0;
    for (set<Land*>::iterator it = lands.begin(); it != lands.end(); it++) {
        /*找到与当前土地连通的同属一个人的土地数*/
    }
    this->maxAdjacentLands = maxAdjacentLands;
}

void Player::EndTurn()
{
    /*赠送骰子*/
    for (int i = 1; i <= this->maxAdjacentLands; i++) {
        /*随机获取set<Land&> lands中的一个，diceAmount加一*/
    }
}
