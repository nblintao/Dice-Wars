#include "Game.h"
#include <ctime>

Game::Game(int chooseAmount = 2) :playerAmount(chooseAmount)
{
}

void Game::Initial()
{
    srand((unsigned)time(NULL));
    /*创建玩家*/
    for (int playerNumber = 1; playerNumber <= 5; playerNumber++) {
        Player newPlayer(playerNumber);
        playerList.push_back(newPlayer);
        //alivePlayer.push_back(newPlayer);
        //numToPlayer[playerNumber] = newPlayer;
    }
    /*读取地图，初始化土地*/
    /*分配土地*/    
}

void Game::Attack(Land& attacker, Land& attacked)
{
    attacker.Attack(attacked);
}


Game::~Game()
{
}
