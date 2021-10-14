#pragma once
#include <string>
#include <iostream>
#include "Position.h"

class Room
{
public:
    Position roomPos;
    std::string roomName;
    bool isDiscovered;
    Room(Position, std::string);
};
