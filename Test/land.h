#ifndef _LAND_H
#define _LAND_H

#include "Grid.h"
#include "Player.h"
#include <iostream>
#include <set>
#include <QString>
#include <QColor>
#include <queue>
using namespace std;

extern const int MAXDICE;

class Player;
class Grid;
class Land
{
private:
    Player *owner;
    set<Grid*> grids;
    set<Land*> adjacentLands;
    int diceAmount;
    QColor color;

public:
    Land();
    ~Land();
    bool IsAdjacent(Land *anotherLand);
    int AdjacentLandsNumber();
    void Attack(Land *attacked,QString& diceAttacker,QString& diceAttacked);
    void ChangeOwner(Player *newOwner);
    void AddGrid(Grid* newGrid);
    void setColor(QColor color);
    void setDice(int diceSum);
    int getDice(){return diceAmount;}
    void Enter();
    void Exit();
    QColor getColor(){return color;}
    bool BelongTo(Player *owner){return this->owner==owner;}
    void AddAdjacent(Land *anotherLand){
        adjacentLands.insert(anotherLand);
    }

};
#endif
