#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <tuple>
#include "Door.h"
#include "Room.h"

typedef std::tuple<bool, Position> roomResult;

enum Direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

class Dungeon
{
private:
	bool createRoom(Position, std::string);
	bool createDoor(Position&, Position&);

public:
	std::unordered_map<std::string, Room> allDungeonRooms;
	std::unordered_map<std::string, Door> allDungeonDoors;
	Dungeon();
	Dungeon(int, bool, bool);
	roomResult createStartRoom();
	roomResult createNextRoom(Position, Direction, std::string);
	std::vector<Door *> getRoomDoors(Position &);
	bool areRoomsConnected(Position &, Position &);
	bool roomExists(Position&);
};
