#pragma once
#include <vector>
#include "Door.h"
#include "Room.h"

enum Direction {NORTH, SOUTH, WEST, EAST};

class Dungeon
{
private:
	Room* lastBuiltRoom;
	void createRoom(Position, std::string);
public:
	std::vector<Room> allDungeonRooms;
	std::vector<Door> allDungeonDoors;
	Dungeon();
	void createStartRoom();
	void createNextRoom(Direction, std::string);
	std::vector<std::string> getRoomDoors (std::string);
};

