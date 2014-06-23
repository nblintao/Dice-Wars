#ifndef _PLAYER_H
#define _PLAYER_H

#include <QColor>
#include<iostream>
#include <set>
#include <vector>
#include "land.h"

using namespace std;

class Player
{
private:
    int ID;
    set<Land*> lands;
    bool alive;
    int maxAdjacentLands;
    int remainDices;
    QColor color;
public:
    Player(int playerNumber);
    ~Player();
    int GetID() const;
    bool IsAlive() const;
    void AddLand(Land *theLand);
    void DeleteLand(Land *theLand);
    void Die();
    void AdjustMaxAdjacentLands();
    void AddDices();
    QColor GetColor() const;
};

inline QColor Player::GetColor() const{
    return color;
}

inline bool Player::IsAlive() const{
    return alive;
}

inline int Player::GetID() const {
    return ID;
}

inline void Player::AddLand(Land *theLand){
    lands.insert(theLand);
}

inline Player::~Player(){
}

inline void Player::Die(){
    std::cout << "PLAYER " << this->ID << " DIE" << endl;
    this->alive = 0;
}

#endif
