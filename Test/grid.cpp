#include "grid.h"

Grid::Grid(QObject *parent) :
    QObject(parent)
{
    color = QColor(Qt::red);
    homeLand = NULL;
}

QColor Grid::getColor(void) const
{
    return color;
}

void Grid::setColor(QColor sColor){
    this->color = sColor;
}

void Grid::setLand(Land& newLand){
    homeLand = &newLand;
}
Land& Grid::getLand(){
    return *(this->homeLand);
}
