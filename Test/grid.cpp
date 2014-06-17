#include "grid.h"

Grid::Grid(QObject *parent) :
    QObject(parent)
{
    color = QColor(Qt::gray);
    homeLand = NULL;
    dice=0;
}

QColor Grid::getColor(void) const
{
    return color;
}

void Grid::setColor(QColor sColor){
    this->color = sColor;
}

void Grid::setLand(Land *newLand){
    homeLand = newLand;
}
void Grid::setDice(int is){
    dice=is;
}
int Grid::getDice() const{
    return dice;
}
Land* Grid::getLand(){
    return homeLand;
}
