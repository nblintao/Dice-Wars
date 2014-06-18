#include "player.h"
#include<iostream>

Player::Player(int playerNumber) :ID(playerNumber),alive(1), remainDices(0)
{
    switch(playerNumber){
        case 0:{
            color = QColor(Qt::yellow);
            break;
        }
        case 1:{
            color = QColor(Qt::red);
            break;
        }
        case 2:{
            color = QColor(Qt::green);
            break;
        }
        default:{
            color = QColor(Qt::black);
            break;
        }
    }

}


Player::~Player()
{
}

void Player::AddLand(Land *theLand)
{
    lands.insert(theLand);
    //this->AdjustMaxAdjacentLands();
}

void Player::DeleteLand(Land *theLand)
{
    lands.erase(theLand);
    if (this->lands.empty()) {
        this->Die();
    }
    //this->AdjustMaxAdjacentLands();
}
void Player::Die()
{
    std::cout << "PLAYER " << this->ID << " DIE" << endl;
    this->alive = 0;
}
void Player::AdjustMaxAdjacentLands()
{
    std::cout<<"AdjustMaxAdjacentLands"<<endl;
    int maxAdjacentLands = 0;
    for (set<Land*>::iterator it = lands.begin(); it != lands.end(); it++) {
        /*找到与当前土地连通的同属一个人的土地数*/
        int adjacentLands = (*it)->AdjacentLandsNumber();
        if(adjacentLands>maxAdjacentLands){
            maxAdjacentLands = adjacentLands;
        }
    }
    this->maxAdjacentLands = maxAdjacentLands;
    std::cout<<"max adjacent lands:"<<maxAdjacentLands<<endl;
}

void Player::AddDices()
{
    /*赠送骰子*/
    vector<Land*> availableLands;
    for(set<Land*>::iterator it=lands.begin();it!=lands.end();it++){
        if((*it)->getDice() != MAXDICE)
            availableLands.push_back(*it);
    }
    int freeDices = remainDices + maxAdjacentLands;
    remainDices = 0;
    for (int i = 1; i <= freeDices; i++) {
        if(!availableLands.empty()){
            int randLandNumber = rand()%availableLands.size();
            Land *randLand = availableLands[randLandNumber];
            randLand->setDice(randLand->getDice()+1);
            if(randLand->getDice() == MAXDICE)
                availableLands.erase(availableLands.begin()+randLandNumber);
        }else{
            remainDices++;
        }
    }
}
