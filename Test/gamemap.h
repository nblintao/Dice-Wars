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

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = 0);
    ~GameMap();
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void gameOver();
    Q_INVOKABLE QColor getColor(int index)const;
    Q_INVOKABLE void enter(int index);
    Q_INVOKABLE void exit(int index);
    Q_INVOKABLE void click(int index);
    Q_INVOKABLE void endTurn();
    Q_INVOKABLE int getDice(int index) const;
    Q_INVOKABLE void setDice(int index,int diceSum);
    Q_INVOKABLE QColor getAttackerColor();
    Q_INVOKABLE QColor getAttackedColor();
    Q_INVOKABLE QColor getPlayerColor();
    Q_INVOKABLE QString getAttackerDice();
    Q_INVOKABLE QString getAttackedDice();
    Q_INVOKABLE int getStatus(){return status;}
    Q_INVOKABLE void setPlayer(int playerAmount){this->playerAmount=playerAmount;}
//    void playerDie(){
//        playerAmount--;
//        if(playerAmount==1)
//            gameOver();
//    }
    void setColor(int index,QColor sColor);
    void AddGrid(Land *theLand,int row,int colum);
    void AssignLand(Player *theplayer, Land *theLand);
    void ChangeAttaker(Land* newLand);
    void FindAdjacent();
    bool IsLastPlayer(){
        int aliveNumber = 0;
        for(vector<Player*>::iterator it=players.begin();it!=players.end();it++){
            Player *theplayer = *it;
            if(theplayer->IsAlive()){
                aliveNumber++;
                alivePlayer = theplayer;
            }
        }
        return aliveNumber==1;
    }
signals:
    void sendColorChange(void);
public slots:
private:
    Grid grids[10][20];
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

#endif // GAMEMAP_H
