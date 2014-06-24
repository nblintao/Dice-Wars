//-------------------------------------------------------------------------------
// 单位：           浙江大学
// 制作人员：        周宇恒 张闻 林涛
// 完成日期:         06/21/2014
// 模块名:          gamemap
// 项目名:          “骰子战争”
//---------------------------------------------------------------------------------
#ifndef _GAMEMAP_H
#define _GAMEMAP_H

#include "grid.h"
#include "land.h"
#include "player.h"
#include <QObject>
#include <QString>
#include <set>
#include <vector>
#include <ctime>
#include <cstdio>

extern const int MAXDICE;
extern const int ROW;
extern const int COLUMN;
extern const int LANDMAX;

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = 0);
    ~GameMap();
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void gameOver();
    Q_INVOKABLE void enter(int index);
    Q_INVOKABLE void exit(int index);
    Q_INVOKABLE void click(int index);
    Q_INVOKABLE void endTurn();
    Q_INVOKABLE int getDice(int index) const;
    Q_INVOKABLE void setDice(int index,int diceSum);
    Q_INVOKABLE QColor getColor(int index) const;
    Q_INVOKABLE QColor getAttackerColor() const;
    Q_INVOKABLE QColor getAttackedColor() const;
    Q_INVOKABLE QColor getPlayerColor() const;
    Q_INVOKABLE QColor getWinnerColor() const;
    Q_INVOKABLE QString getAttackerDice() const;
    Q_INVOKABLE QString getAttackedDice() const;
    Q_INVOKABLE int getStatus() const;
    Q_INVOKABLE void setPlayer(int playerAmount);
    void setColor(int index,QColor sColor);  //用于设定该领地在地图上的颜色，与领地所述的玩家编号有关
    void AddGrid(Land *theLand,int row,int colum);  //用于创建地图
    void AssignLand(Player *theplayer, Land *theLand);  //确定领地的归属，将领地分配给特定的玩家
    void ChangeAttaker(Land* newLand);  //用户如果先后单击两次己方领地，则视为更换发动攻击的地块
    void FindAdjacent();  //在地图创建之后存储所有地区的邻接信息，以便攻击时判断此次攻击是否有效
    bool IsLastPlayer();  //判断当前玩家是否是最后一个，如果是，判其获胜，游戏结束
    Q_INVOKABLE int row() const;
    Q_INVOKABLE int column() const;
signals:
    void sendColorChange(void);
public slots:
private:
    static const int ROW=20;
    static const int COLUMN=40;
    Grid grids[ROW][COLUMN];
    set<Land*> lands;
    vector<Player*> players;
    Player *alivePlayer;
    QColor attackerColor,attackedColor;
    QString diceAttacker,diceAttacked;
    Land *attacker;
    Player *playerNow;
    int playerAmount;
    int status;
};

inline int GameMap::getStatus() const{
     return status;
}

inline void GameMap::setPlayer(int playerAmount){
    this->playerAmount=playerAmount;
}

inline int GameMap::row() const{
    return ROW;
}

inline int GameMap::column() const{
    return COLUMN;
}

inline GameMap::~GameMap(){     //the destructor of map
}

inline QColor GameMap::getColor(int index) const{
    return grids[index/COLUMN][index%COLUMN].getColor();
}

inline int GameMap::getDice(int index) const{
    return grids[index/COLUMN][index%COLUMN].getDice();
}

inline QColor GameMap::getAttackerColor() const{
    return attackerColor;
}

inline QColor GameMap::getAttackedColor() const{
    return attackedColor;
}

inline QString GameMap::getAttackerDice() const{
    return diceAttacker;
}

inline QString GameMap::getAttackedDice() const{
    return diceAttacked;
}

inline QColor GameMap::getPlayerColor() const{
    return playerNow->GetColor();
}

inline QColor GameMap::getWinnerColor() const{
    if (NULL==alivePlayer)
        return QColor(255,255,255);
    else
        return alivePlayer->GetColor();
}

#endif // GAMEMAP_H
