#pragma once
#include <vector>
#include <unordered_map>
#include "Door.h"
#include "Room.h"

enum Direction {NORTH, SOUTH, WEST, EAST};

class Dungeon
{
private:
	Room* lastBuiltRoom;
	void createRoom(Position, std::string);
public:
	std::unordered_map<std::string, Room> allDungeonRooms;
	std::unordered_map<std::string, Door> allDungeonDoors;
	Dungeon();
	void createStartRoom();
	void createNextRoom(Direction, std::string);
	std::vector<std::string> getRoomDoors (std::string);
};

