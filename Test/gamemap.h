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
    void setColor(int index,QColor sColor);
    void AddGrid(Land *theLand,int row,int colum);
    void AssignLand(Player *theplayer, Land *theLand);
    void ChangeAttaker(Land* newLand);
    void FindAdjacent();
    bool IsLastPlayer();
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
