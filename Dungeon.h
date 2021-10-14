#pragma once
#include <vector>
#include <unordered_map>
#include "Door.h"
#include "Room.h"

enum Direction {NORTH, SOUTH, WEST, EAST};

class Dungeon
{
private:
	bool createRoom(Position, std::string);
public:
	std::unordered_map<std::string, Room> allDungeonRooms;
	std::unordered_map<std::string, Door> allDungeonDoors;
	Dungeon();
	Position createStartRoom();
	Position createNextRoom(Position, Direction, std::string);
	std::vector<Door*> getRoomDoors (Position&);
	bool areRoomsConnected(Position&, Position&);
};

