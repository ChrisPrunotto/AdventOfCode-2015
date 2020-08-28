#include "day3_funcs.h"
#include <map>
#include <utility>
#include <string>
#include <iostream>

void dropPresent(bool bSantasTurn, std::pair<int, int> &santaCoordPair, std::pair<int, int> &roboSantaCoordPair, std::map<std::pair<int, int>, int> &coordinateGrid)
{
    if (bSantasTurn)
    {
        if (coordinateGrid.find({santaCoordPair}) == coordinateGrid.end()){
            coordinateGrid.insert({santaCoordPair,1});
        }
        else{
            coordinateGrid[{santaCoordPair}] +=1;
        }
    }
    else {
        if (coordinateGrid.find({roboSantaCoordPair}) == coordinateGrid.end()){
            coordinateGrid.insert({roboSantaCoordPair,1});
        }
        else{
            coordinateGrid[{roboSantaCoordPair}] +=1;
        }
    }
}