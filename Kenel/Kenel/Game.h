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
    /*鼠标移位后执行，输入所在的Grid的位置*/
    void ChangePosition();
    void ChooseLand1();
    void ChooseLand2();
    /*输入攻击和被攻击的Land，必须是符合条件的*/
    void Attack(Land& attacker, Land& attacked);
    ~Game();
};
#endif
