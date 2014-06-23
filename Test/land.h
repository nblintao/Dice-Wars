#ifndef _LAND_H
#define _LAND_H

#include <QString>
#include <QColor>
#include <queue>
#include <set>
#include <iostream>

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
    bool IsAdjacent(Land *anotherLand);  //用于判断两领地是否相邻，决定能否相互攻击
    int AdjacentLandsNumber();  //获取邻接地的数量
    void Attack(Land *attacked,QString& diceAttacker,QString& diceAttacked);//执行攻击指令，并处理骰子增减等问题
    void ChangeOwner(Player *newOwner);  //若攻击成功，需要交换领地的归属
    void AddGrid(Grid* newGrid);  //在创建领地时被调用
    void SetColor(QColor color);  //设定领地颜色
    void SetDice(int diceSum);  //设定骰子数量
    int GetDice() const;    //用于访问私有变量diceAmount
    void Enter();
    void Exit();
    QColor GetColor() const;
    bool BelongTo(Player *owner);  //判断领地是否属于该玩家
    void AddAdjacent(Land *anotherLand);  //更新与该领地相邻的区域
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
