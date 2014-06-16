#include "grid.h"

Grid::Grid(QObject *parent) :
    QObject(parent)
{
    color = QColor(Qt::red);
}

QColor Grid::getColor(void) const
{
    return color;
}

void Grid::setColor(QColor sColor){
    this->color = sColor;
    emit sendColorChange();
}
