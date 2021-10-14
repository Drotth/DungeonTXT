#include <iostream>
#include <unistd.h>
#include "Dungeon.h"
#include "Map.h"

using namespace std;

int main()
{
	Dungeon newDungeon;

	// Verify room/door setups
	// cout << "Nbr of rooms: " << newDungeon.allDungeonRooms.size() << endl;
	// cout << "Nbr of doors: " << newDungeon.allDungeonDoors.size() << endl;

	// for (auto i = newDungeon.allDungeonRooms.begin(); i != newDungeon.allDungeonRooms.end(); i++)
	// {
	// 	cout << i->second.roomName << "\t" << i->second.roomPos << endl;
	// }

	// for (auto i2 = newDungeon.allDungeonDoors.begin(); i2 != newDungeon.allDungeonDoors.end(); i2++)
	// {
	// 	cout << i2->second.doorName << " goes to rooms: " << i2->second.roomA << "\t" << i2->second.roomB << endl;
	// }

	// // Verify get doors in room
	// string currentRoom = "Room 2";
	// vector<string> doors = newDungeon.getRoomDoors(currentRoom);

	// cout << "Doors in " << currentRoom << endl;
	// for (string door : doors)
	// {
	// 	cout << door << endl;
	// }

	// Verify maps
	Map map(newDungeon.allDungeonRooms, newDungeon.allDungeonDoors);
	map.calculateDungeonSize();
	map.printMap();
}
