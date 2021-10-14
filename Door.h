#pragma once
#include <string>
#include "Position.h"

class Door
{
public:
    std::string doorName;
    Position* roomA;
    Position* roomB;
    Door(std::string, Position&, Position&);
};
