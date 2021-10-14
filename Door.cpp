#include "Door.h"

Door::Door(std::string name, Position& roomAId, Position& roomBId)
{
    doorName = name;
    roomA = &roomAId;
    roomB = &roomBId;
}

