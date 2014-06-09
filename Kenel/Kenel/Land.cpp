#include "Land.h"


Land::Land()
{
}


Land::~Land()
{
}

bool Land::IsAdjacent(Land& anotherLand)
{
    return adjacentLands.count(anotherLand);
}