#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "Dungeon.h"

enum ROOMPART {TOP, MIDDLE, BOTTOM};

class Map
{
private:
	int lowestX;
	int highestX;
	int lowestY;
	int highestY;
	std::string map;
	std::unordered_map<std::string, Room> *allDungeonRooms;
	std::unordered_map<std::string, Door> *allDungeonDoors;
	Dungeon *dungeon;
	
	void calculateDungeonSize();
	void drawYDividers(int);
	void drawRowRooms(int, ROOMPART);

public:
	Map(Dungeon&);
	void printMap();
};