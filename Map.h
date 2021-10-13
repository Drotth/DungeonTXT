#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "Dungeon.h"

class Map
{
public:
	std::unordered_map<std::string, Room>* allDungeonRooms;
	std::unordered_map<std::string, Door>* allDungeonDoors;
	Map(std::unordered_map<std::string, Room>&, std::unordered_map<std::string, Door>&);
    void printMap();
};