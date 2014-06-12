#include "Game.h"
#include <ctime>

Game::Game(int chooseAmount = 2) :playerAmount(chooseAmount)
{
}

void Game::Initial()
{
    srand((unsigned)time(NULL));
    for (int playerNumber = 1; playerNumber <= 5; playerNumber++) {
        Player newPlayer(playerNumber);
        playerList.push_back(newPlayer);
        alivePlayer.push_back(newPlayer);
        numToPlayer[playerNumber] = newPlayer;
    }
}

void Game::Attack(Land& attacker, Land& attacked)
{
    attacker.Attack(attacked);
}


Game::~Game()
{
}
