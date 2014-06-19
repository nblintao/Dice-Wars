#include "player.h"
#include<iostream>

Player::Player(int playerNumber) :ID(playerNumber),alive(1), remainDices(0)
{
    switch(playerNumber){        //different grid color represent different players' land.
        case 0:{
            color = QColor(255,255,0);
            break;
        }
        case 1:{
            color = QColor(255,0,0);
            break;
        }
        case 2:{
            color = QColor(0,255,0);
            break;
        }
        case 3:{
            color = QColor(0,0,255);
            break;
        }
        case 4:{
            color = QColor(255,0,255);
            break;
        }
        case 5:{
            color = QColor(0,255,255);
            break;
        }
        default:{
            color = QColor(255,255,255);
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
    //std::cout<<"AdjustMaxAdjacentLands"<<endl;
    int maxAdjacentLands = 0;
    for (set<Land*>::iterator it = lands.begin(); it != lands.end(); it++) {
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
    vector<Land*> availableLands;
    for(set<Land*>::iterator it=lands.begin();it!=lands.end();it++){
        if((*it)->getDice() != MAXDICE)
            availableLands.push_back(*it);
    }
    int freeDices = remainDices + maxAdjacentLands;   //decide the number of dices will be added.
    remainDices = 0;
    for (int i = 1; i <= freeDices; i++) {
        if(!availableLands.empty()){
            int randLandNumber = rand()%availableLands.size();   //choose where to add randomly.
            Land *randLand = availableLands[randLandNumber];
            randLand->setDice(randLand->getDice()+1);
            if(randLand->getDice() == MAXDICE)     //when the land is full, dices cannot be added.
                availableLands.erase(availableLands.begin()+randLandNumber);
        }else{
            remainDices++;
        }
    }
}
