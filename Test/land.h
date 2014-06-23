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
extern const int ROW;
extern const int COLUMN;

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
    void SetColor(QColor color);
    void SetDice(int diceSum);
    int GetDice() const;
    void Enter();
    void Exit();
    QColor GetColor() const;
    bool BelongTo(Player *owner);
    void AddAdjacent(Land *anotherLand);
};

inline void Land::Enter(){
    SetColor(color.lighter(80));
}

inline void Land::Exit(){
    SetColor(color);
}

inline bool Land::IsAdjacent(Land *anotherLand){
    return adjacentLands.count(anotherLand);   //judge whether two lands are adjacent.
}

inline Land::~Land(){
}

inline void Land::AddGrid(Grid *newGrid){
    grids.insert(newGrid);
}

inline int  Land::GetDice() const{
    return diceAmount;
}

inline QColor Land::GetColor() const{
    return color;
}

inline bool Land::BelongTo(Player *owner){
    return this->owner==owner;
}

inline  void Land::AddAdjacent(Land *anotherLand){
    adjacentLands.insert(anotherLand);
}

#endif
