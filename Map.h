#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "Dungeon.h"

class Map
{
private:
	int lowestX;
	int highestX;
	int lowestY;
	int highestY;
	std::string map;

	void addYDivider(int);

public:
	std::unordered_map<std::string, Room> *allDungeonRooms;
	std::unordered_map<std::string, Door> *allDungeonDoors;
	Map(std::unordered_map<std::string, Room> &, std::unordered_map<std::string, Door> &);
	void calculateDungeonSize();
	void printMap();
};