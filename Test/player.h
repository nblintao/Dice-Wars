#ifndef _PLAYER_H
#define _PLAYER_H

#include <QColor>
#include <set>
#include <vector>
#include "land.h"

using namespace std;

//class Land;

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
    int GetID(){return ID;}
    bool IsAlive(){return alive;}
    void AddLand(Land *theLand);
    void DeleteLand(Land *theLand);
    void Die();
    void AdjustMaxAdjacentLands();
    void AddDices();
//    void EndTurn();
    QColor getColor(){
        return color;
    }
};
#endif
