#include "grid.h"

Grid::Grid(QObject *parent) :  QObject(parent){
    color = QColor(Qt::gray);
    homeLand = NULL;
    dice=0;
}

