#include <iostream>
#include <unistd.h>
#include "Dungeon.h"
#include "Map.h"
#include "Player.h"

using namespace std;

int main()
{
	Dungeon newDungeon(10, 0, 0, true, true);
	// Dungeon newDungeon;

	Map map(newDungeon);

	Player player;

	player.currentRoom = Position(0,0);
	map.setPlayerPos(player.currentRoom);

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
	map.printMap();

	// string input;
	
	// while (input != "exit"){

	// 	cin >> input;
	// 	if (input == "w"){
	// 		player.currentRoom = player.currentRoom + Position(0,1);
	// 	}
	// 	else if (input == "a"){
	// 		player.currentRoom = player.currentRoom + Position(-1,0);
	// 	}
	// 	else if (input == "s"){
	// 		player.currentRoom = player.currentRoom + Position(0,-1);
	// 	}
	// 	else if (input == "d"){
	// 		player.currentRoom = player.currentRoom + Position(1,0);
	// 	} else input = "exit";

	// 	map.setPlayerPos(player.currentRoom);
	// 	map.printMap();
	// }
}

/*

Ideas:

Scenario: set of Dungeons with individual goals, for one big final win
	- Could be rng generated based on the goal of the previous one, e.g:
	  If lastRoom was find a key, next room is find chest to unlock, etc
	- Rooms could have "isWin" var of different types: isExitWin, isBossWin etc
	- Or items, doors, enemies could have "isWin" attribute

Goals: E.g. SLay the big boss, find the exit, fins a specific item, unlock a specific chest
	- Connected to the "isWin" thing from above.

Rng dungeon generation: as distance from start room increases, loot should get
better and enemies get tougher and/or increase.
	- Could be implemented with a A* (shortest path) calc per individual room
	- Dungeons should get tougher as Scenario progresses

*/
