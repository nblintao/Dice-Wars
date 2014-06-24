#ifndef _PLAYER_H
#define _PLAYER_H

#include <QColor>
#include <set>
#include <vector>
#include<iostream>

using namespace std;
class Land;

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
    bool IsAlive() const;  //通过对地图的扫描，得知该玩家是否还有领地
    void AddLand(Land *theLand);  //创建时给玩家分配领地，以及进攻成功后获得领地
    void DeleteLand(Land *theLand);  //被他人进攻后失去领地
    void Die();                   //设置该玩家已死亡，此后不再出现有关操作
    void AdjustMaxAdjacentLands();  //获得最大的连续领地数
    void AddDices();              //在进攻成功或一轮结束后，用于给该玩家的各个领地随机分配相应数量的骰子
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
