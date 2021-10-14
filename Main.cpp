#include <iostream>
#include <unistd.h>
#include "Dungeon.h"
#include "Map.h"
#include "Player.h"

using namespace std;

int main()
{
	Dungeon newDungeon;

	Player player;
	player.currentRoom = Position(0,0);

	// // Verify room/door setups
	// cout << "Nbr of rooms: " << newDungeon.allDungeonRooms.size() << endl;
	// cout << "Nbr of doors: " << newDungeon.allDungeonDoors.size() << endl;

	// for (auto i = newDungeon.allDungeonRooms.begin(); i != newDungeon.allDungeonRooms.end(); i++)
	// {
	// 	cout << i->second.roomName << "\t" << i->second.roomPos << endl;
	// }

	// for (auto i2 = newDungeon.allDungeonDoors.begin(); i2 != newDungeon.allDungeonDoors.end(); i2++)
	// {
	// 	cout << i2->second.doorName << " goes to rooms: " << *i2->second.roomA << "\t" << *i2->second.roomB << endl;
	// }

	// // // Verify get doors in room
	// Position currentRoom = newDungeon.allDungeonRooms.at("x:0,y:2").roomPos;
	// // vector<string> doors = newDungeon.getRoomDoors(currentRoom);
	// vector<Door*> doors = newDungeon.getRoomDoors(currentRoom);

	// // cout << "Doors in " << currentRoom << endl;
	// // for (string door : doors)
	// // {
	// // 	cout << door << endl;
	// // }

	// cout << "Doors in \"" << currentRoom << "\":" << endl;
	// for (Door* door : doors)
	// {
	// 	cout << door->doorName << endl;
	// }

	// Verify maps
	Map map(newDungeon);
	map.setPlayerPos(player.currentRoom);
	map.printMap();
}
