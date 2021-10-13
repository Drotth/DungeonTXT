#include <iostream>
#include "Dungeon.h"

using namespace std;

int main()
{
	Dungeon newDungeon;

	// Verify room/door setups
	cout << "Nbr of rooms: " << newDungeon.allDungeonRooms.size() << endl;
	cout << "Nbr of doors: " << newDungeon.allDungeonDoors.size() << endl;

	for (int index = 0; index < newDungeon.allDungeonRooms.size(); index++)
	{
		cout << "[" << index << "]: " << 
		newDungeon.allDungeonRooms.at(index).roomName << "\t" <<
		newDungeon.allDungeonRooms.at(index).roomPos << endl;
	}

	// for (Door door : newDungeon.allDungeonDoors)
	// {
	// 	cout << "Doorlist: Room A: " << door.roomA << endl;
	// 	cout << "Doorlist: Room B: " << door.roomB << endl;
	// }

	// Verify get doors in room
	// string currentRoom = "Room 2";
	// vector<string> doors = newDungeon.getRoomDoors(currentRoom);

	// cout << "Doors in " << currentRoom << endl;
	// for (string door : doors)
	// {
	// 	cout << door << endl;
	// }
}
