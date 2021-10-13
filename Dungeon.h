#pragma once
#include <vector>
#include "Door.h"
#include "Room.h"

class Dungeon
{
public:
	std::vector<Room> allDungeonRooms;
	std::vector<Door> allDungeonDoors;
	Dungeon();
	std::vector<std::string> getRoomDoors (std::string);
};

