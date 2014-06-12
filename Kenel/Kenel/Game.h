#ifndef _GAME_H
#define _GAME_H

#include "Grid.h"
#include "Land.h"
#include "Player.h"
#include <list>
#include <map>

class Game
{
private:
    int playerAmount;
    list<Player> playerList;
    list<Land> landList;
    //list<Player&> alivePlayer;
    //map<int, Player&> numToPlayer;

public:
    Game(int chooseAmount);
    void Initial();
    /*�����λ��ִ�У��������ڵ�Grid��λ��*/
    void ChangePosition();
    void ChooseLand1();
    void ChooseLand2();
    /*���빥���ͱ�������Land�������Ƿ���������*/
    void Attack(Land& attacker, Land& attacked);
    ~Game();
};
#endif
