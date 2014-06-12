#ifndef _PLAYER_H
#define _PLAYER_H

#include <set>
using namespace std;

class Land;

class Player
{
private:
    int ID;
    set<Land&> lands;
    //int color;
    bool alive;
    int maxAdjacentLands;
    int remainDices;
public:
    Player(int playerNumber);
    ~Player();
    void AddLand(Land& theLand);
    void DeleteLand(Land& theLand);
};
#endif
